/**
 * @file object_pool.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — fixed-capacity object pool, no hot-path malloc.
 *
 * One contiguous slab of correctly-aligned raw storage, carved into slots, with
 * the free slots threaded into an intrusive singly-linked list *through the
 * storage itself* — a free slot holds the index of the next free slot, so the
 * free list costs no extra memory and acquire/release are O(1) with no
 * allocation and no search.
 *
 * The points this question is really testing:
 *   - `alignas(T)` on the storage; a slab of `char` is not aligned for T.
 *   - placement `new` to construct, explicit `p->~T()` to destroy. The pool
 *     owns raw bytes; it must never let a slot's destructor run twice.
 *   - the destructor must destroy whatever is still outstanding.
 *   - `std::launder` after placement-new into reused storage.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <new>
#include <string>
#include <utility>
#include <vector>

template <typename T, std::size_t Capacity>
class ObjectPool {
 public:
  static_assert(Capacity > 0, "a pool needs at least one slot");

  ObjectPool() {
    // Thread every slot onto the free list, in order.
    for (std::size_t i = 0; i < Capacity; ++i) next_[i] = i + 1;
    free_head_ = 0;
  }

  ~ObjectPool() { destroyOutstanding(); }

  // A pool owns raw storage and hands out pointers into it; copying or moving
  // one would dangle every outstanding pointer.
  ObjectPool(const ObjectPool&) = delete;
  ObjectPool& operator=(const ObjectPool&) = delete;

  /// Constructs a T in a free slot. @return nullptr when the pool is exhausted
  /// — callers on a latency-critical path check this rather than catch.
  template <typename... Args>
  T* acquire(Args&&... args) {
    if (free_head_ == kNoSlot) return nullptr;

    const std::size_t slot = free_head_;
    free_head_ = next_[slot];

    T* obj = ::new (slotAddress(slot)) T(std::forward<Args>(args)...);
    live_[slot] = true;
    ++outstanding_;
    return std::launder(obj);
  }

  /// Destroys @p obj and returns its slot to the free list.
  void release(T* obj) {
    if (obj == nullptr) return;

    const std::size_t slot = slotOf(obj);
    obj->~T();
    live_[slot] = false;
    next_[slot] = free_head_;
    free_head_ = slot;
    --outstanding_;
  }

  std::size_t outstanding() const { return outstanding_; }
  std::size_t available() const { return Capacity - outstanding_; }
  static constexpr std::size_t capacity() { return Capacity; }

 private:
  static constexpr std::size_t kNoSlot = Capacity;

  void* slotAddress(std::size_t slot) { return &storage_[slot * sizeof(T)]; }

  std::size_t slotOf(const T* obj) const {
    const auto* raw = reinterpret_cast<const unsigned char*>(obj);
    return static_cast<std::size_t>(raw - storage_) / sizeof(T);
  }

  void destroyOutstanding() {
    for (std::size_t i = 0; i < Capacity; ++i) {
      if (!live_[i]) continue;
      std::launder(reinterpret_cast<T*>(&storage_[i * sizeof(T)]))->~T();
      live_[i] = false;
    }
    outstanding_ = 0;
  }

  alignas(T) unsigned char storage_[Capacity * sizeof(T)];
  std::size_t next_[Capacity] = {};
  bool live_[Capacity] = {};
  std::size_t free_head_ = kNoSlot;
  std::size_t outstanding_ = 0;
};

// ------------------------------------------------------------------- TESTS --

namespace {

int g_live_instances = 0;

/// Counts its own construction/destruction so double-destroy or leaked slots
/// show up as a non-zero balance.
struct Tracked {
  Tracked(int v, std::string tag) : value(v), name(std::move(tag)) {
    ++g_live_instances;
  }
  ~Tracked() { --g_live_instances; }
  Tracked(const Tracked&) = delete;
  Tracked& operator=(const Tracked&) = delete;

  int value;
  std::string name;
};

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;

  {
    ObjectPool<Tracked, 3> pool;
    passed &= expect("starts empty", pool.outstanding() == 0);
    passed &= expect("full capacity available", pool.available() == 3);

    Tracked* a = pool.acquire(1, "a");
    Tracked* b = pool.acquire(2, "b");
    Tracked* c = pool.acquire(3, "c");

    passed &= expect("acquire returns storage", a && b && c);
    passed &= expect("ctor args forwarded",
                     a != nullptr && a->value == 1 && a->name == "a");
    passed &= expect("distinct slots", a != b && b != c && a != c);
    passed &= expect("three constructed", g_live_instances == 3);
    passed &= expect("pool exhausted", pool.acquire(4, "d") == nullptr);
    passed &= expect("none available", pool.available() == 0);

    // Releasing must run the destructor and hand the slot back.
    pool.release(b);
    passed &= expect("destructor ran on release", g_live_instances == 2);
    passed &= expect("slot returned", pool.available() == 1);

    Tracked* reused = pool.acquire(9, "reused");
    passed &= expect("freed slot is reused", reused == b);
    passed &= expect("reused slot is a fresh object",
                     reused != nullptr && reused->value == 9);
    passed &= expect("constructed again", g_live_instances == 3);

    pool.release(nullptr);  // must be a harmless no-op
    passed &= expect("release(nullptr) is a no-op", pool.outstanding() == 3);
  }
  // Pool destroyed with three objects still outstanding.
  passed &= expect("dtor destroys outstanding objects", g_live_instances == 0);

  // Full drain then refill, to confirm the free list survives being emptied.
  {
    ObjectPool<Tracked, 2> pool;
    Tracked* x = pool.acquire(1, "x");
    Tracked* y = pool.acquire(2, "y");
    pool.release(x);
    pool.release(y);
    passed &= expect("all released", pool.outstanding() == 0);
    passed &= expect("nothing alive", g_live_instances == 0);

    passed &=
        expect("refill after full drain", pool.acquire(3, "z") != nullptr);
    passed &= expect("refill again", pool.acquire(4, "w") != nullptr);
    passed &= expect("exhausted once more", pool.acquire(5, "v") == nullptr);
  }
  passed &= expect("balanced at end", g_live_instances == 0);

  // Alignment is a correctness requirement, not a nicety.
  {
    ObjectPool<double, 4> pool;
    double* d = pool.acquire(1.5);
    passed &=
        expect("aligned for T",
               reinterpret_cast<std::uintptr_t>(d) % alignof(double) == 0);
    passed &= expect("value stored", d != nullptr && *d == 1.5);
  }

  return passed;
}

}  // namespace

#ifndef RunTests
int main() {
  if (doTestsPass()) {
    std::cout << "ALL TESTS PASS." << std::endl;
  } else {
    std::cout << "TESTS FAILED." << std::endl;
  }
  return 0;
}
#endif
