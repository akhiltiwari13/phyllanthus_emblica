/**
 * @file lru_cache.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief PRACTICE — O(1) LRU cache. Target: 25 minutes.
 *
 * Fixed-capacity cache that evicts the least-recently-used entry. Every
 * operation O(1) — no scan for the victim.
 *
 *   LruCache(capacity)
 *   optional<Value> get(key)     on a hit, promote to most-recently-used
 *   void put(key, value)         insert or update, promoting either way;
 *                                evict the LRU entry only when over capacity
 *   bool contains(key)           does NOT count as a use
 *   bool erase(key)
 *   vector<Key> keysByRecency()  most- to least-recently used
 *   size() / capacity() / hits() / misses()
 *
 * The shape is a list ordered by recency plus a map from key to its position.
 * Pick a list whose iterators stay valid when other elements are inserted and
 * erased, and move a node with splice rather than erasing and reinserting it.
 *
 * Traps worth pausing on:
 *   - get() mutates. A const get() cannot promote.
 *   - put() on a key already present must not evict anything.
 *   - evicting from the list is only half the job; the map has to lose the key
 *     too, or it grows forever and ends up holding dangling iterators.
 *   - capacity 0 must be inert, not a crash.
 *
 * Run it: the tests below are the spec. Reference in solutions/.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

template <typename Key, typename Value>
class LruCache {
 public:
  explicit LruCache(std::size_t capacity) : capacity_(capacity) {}

  std::optional<Value> get(const Key& key) {
    (void)key;
    return std::nullopt;  // TODO
  }

  void put(const Key& key, Value value) {
    (void)key, (void)value;  // TODO
  }

  bool contains(const Key& key) const {
    (void)key;
    return false;  // TODO
  }

  bool erase(const Key& key) {
    (void)key;
    return false;  // TODO
  }

  std::vector<Key> keysByRecency() const { return {}; }  // TODO

  std::size_t size() const { return 0; }  // TODO

  std::size_t capacity() const { return capacity_; }

  std::size_t hits() const { return 0; }  // TODO

  std::size_t misses() const { return 0; }  // TODO

 private:
  std::size_t capacity_;
  // TODO: recency list + key -> position index
};

// ------------------------------------------------------------------- TESTS --

namespace {

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

using Keys = std::vector<std::string>;

bool doTestsPass() {
  bool passed = true;

  {
    LruCache<std::string, int> cache(3);
    passed &= expect("starts empty", cache.size() == 0);
    passed &= expect("miss on empty", !cache.get("a").has_value());
    passed &= expect("miss counted", cache.misses() == 1);

    cache.put("a", 1);
    cache.put("b", 2);
    cache.put("c", 3);
    passed &= expect("holds three", cache.size() == 3);
    passed &= expect("insertion order is MRU-first",
                     cache.keysByRecency() == (Keys{"c", "b", "a"}));

    passed &= expect("hit returns value", cache.get("a") == 1);
    passed &=
        expect("hit promotes", cache.keysByRecency() == (Keys{"a", "c", "b"}));
    passed &= expect("hit counted", cache.hits() == 1);

    // "b" is now least-recently-used, so it is the one to go.
    cache.put("d", 4);
    passed &= expect("still at capacity", cache.size() == 3);
    passed &= expect("LRU evicted", !cache.contains("b"));
    passed &=
        expect("survivors intact", cache.contains("a") && cache.contains("c"));
    passed &= expect("order after eviction",
                     cache.keysByRecency() == (Keys{"d", "a", "c"}));

    // Updating an existing key promotes without evicting.
    cache.put("c", 33);
    passed &= expect("update keeps size", cache.size() == 3);
    passed &= expect("update stores new value", cache.get("c") == 33);
    passed &= expect("update promotes",
                     cache.keysByRecency() == (Keys{"c", "d", "a"}));

    passed &= expect("erase existing", cache.erase("d"));
    passed &= expect("erase is idempotent-safe", !cache.erase("d"));
    passed &= expect("size drops", cache.size() == 2);
    passed &=
        expect("order after erase", cache.keysByRecency() == (Keys{"c", "a"}));
  }

  // Capacity 1: every insert evicts the previous entry.
  {
    LruCache<int, int> cache(1);
    cache.put(1, 10);
    cache.put(2, 20);
    passed &= expect("capacity 1 holds one", cache.size() == 1);
    passed &= expect("older key evicted", !cache.get(1).has_value());
    passed &= expect("newest key kept", cache.get(2) == 20);
  }

  // Capacity 0 must be inert, not a crash.
  {
    LruCache<int, int> cache(0);
    cache.put(1, 10);
    passed &= expect("zero capacity stores nothing", cache.size() == 0);
    passed &= expect("zero capacity always misses", !cache.get(1).has_value());
  }

  // A repeatedly-read key must never be evicted.
  {
    LruCache<int, int> cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    for (int i = 3; i < 10; ++i) {
      cache.get(1);     // keep 1 hot
      cache.put(i, i);  // evicts whatever is cold
    }
    passed &= expect("hot key survives churn", cache.get(1) == 1);
    passed &= expect("cold key long gone", !cache.get(2).has_value());
    passed &= expect("capacity respected throughout", cache.size() == 2);
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
