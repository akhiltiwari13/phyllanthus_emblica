/**
 * @file lru_cache.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — O(1) LRU cache, intrusive list + hash map.
 *
 * A std::list of {key, value} nodes ordered most- to least-recently used, plus
 * a hash map from key to list iterator. std::list iterators stay valid across
 * every insertion and every erasure of *other* elements, which is what makes
 * storing them in the map safe — a std::vector-backed list would invalidate
 * them on the first reallocation.
 *
 * Both get() and put() are O(1): splice() moves a node to the front by
 * relinking pointers, without allocating or copying the value.
 *
 * The details that get this question wrong:
 *   - get() is a *mutation*: a hit must promote the entry.
 *   - put() on an existing key updates and promotes, it does not evict.
 *   - the evicted key must be erased from the map too, or the map grows without
 *     bound and later holds dangling iterators.
 *   - capacity 0 must not fall over.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class LruCache {
 public:
  explicit LruCache(std::size_t capacity) : capacity_(capacity) {}

  /// Looks up @p key and, on a hit, promotes it to most-recently-used.
  std::optional<Value> get(const Key& key) {
    const auto it = index_.find(key);
    if (it == index_.end()) {
      ++misses_;
      return std::nullopt;
    }
    ++hits_;
    entries_.splice(entries_.begin(), entries_, it->second);  // O(1) promote
    return it->second->value;
  }

  /// Inserts or updates @p key, promoting it. Evicts the least-recently-used
  /// entry when that would exceed capacity.
  void put(const Key& key, Value value) {
    if (capacity_ == 0) return;

    const auto it = index_.find(key);
    if (it != index_.end()) {
      it->second->value = std::move(value);
      entries_.splice(entries_.begin(), entries_, it->second);
      return;
    }

    if (entries_.size() == capacity_) evictLru();

    entries_.push_front(Entry{key, std::move(value)});
    index_.emplace(key, entries_.begin());
  }

  bool contains(const Key& key) const { return index_.contains(key); }

  bool erase(const Key& key) {
    const auto it = index_.find(key);
    if (it == index_.end()) return false;
    entries_.erase(it->second);
    index_.erase(it);
    return true;
  }

  /// Keys from most- to least-recently used. Test/diagnostic aid.
  std::vector<Key> keysByRecency() const {
    std::vector<Key> keys;
    keys.reserve(entries_.size());
    for (const Entry& entry : entries_) keys.push_back(entry.key);
    return keys;
  }

  std::size_t size() const { return entries_.size(); }
  std::size_t capacity() const { return capacity_; }
  std::size_t hits() const { return hits_; }
  std::size_t misses() const { return misses_; }

 private:
  struct Entry {
    Key key;
    Value value;
  };
  using List = std::list<Entry>;

  void evictLru() {
    index_.erase(entries_.back().key);  // must go, or the map leaks
    entries_.pop_back();
  }

  std::size_t capacity_;
  List entries_;  // front = MRU
  std::unordered_map<Key, typename List::iterator> index_;
  std::size_t hits_ = 0;
  std::size_t misses_ = 0;
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
