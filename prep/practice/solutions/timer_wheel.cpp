/**
 * @file timer_wheel.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — single-level timing wheel, O(1) schedule/expire.
 *
 * An order gateway arms a timeout per in-flight order and cancels the vast
 * majority of them when the ack arrives. A std::multimap or priority_queue
 * makes that O(log n) per arm and per cancel; a timing wheel makes it O(1).
 *
 * The wheel is an array of `Slots` buckets indexed by `deadline % Slots`, so
 * advancing the clock by one tick only inspects the single bucket that can
 * expire. Deadlines further out than one full revolution would alias onto an
 * earlier slot, so each entry carries its absolute deadline and a rotation is
 * skipped when the deadline has not been reached yet — the standard trick
 * before reaching for a hierarchical (multi-level) wheel.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

class TimerWheel {
 public:
  explicit TimerWheel(std::size_t slots) : slots_(slots) {}

  /// Arms @p id to fire @p delay ticks from now.
  /// @return false if @p id is already armed or @p delay is zero.
  bool schedule(std::uint64_t id, std::uint64_t delay) {
    if (delay == 0 || index_.contains(id)) return false;

    const std::uint64_t deadline = now_ + delay;
    slots_[deadline % slots_.size()].push_back(Entry{id, deadline});
    index_.emplace(id, deadline);
    return true;
  }

  /// Disarms a timer. O(1) lookup; the bucket entry is left as a tombstone and
  /// dropped when its slot is next swept, which keeps cancel — the hot path —
  /// free of any list walk.
  bool cancel(std::uint64_t id) { return index_.erase(id) == 1; }

  /// Advances the clock one tick. @return the ids that fired, in arm order.
  std::vector<std::uint64_t> tick() {
    ++now_;
    std::vector<std::uint64_t> fired;
    auto& bucket = slots_[now_ % slots_.size()];

    std::vector<Entry> carried;  // deadlines a full revolution or more away
    for (const Entry& entry : bucket) {
      const auto it = index_.find(entry.id);
      if (it == index_.end() || it->second != entry.deadline)
        continue;  // cancelled

      if (entry.deadline > now_) {
        carried.push_back(entry);  // aliased onto this slot, not due yet
        continue;
      }
      fired.push_back(entry.id);
      index_.erase(it);
    }
    bucket.swap(carried);
    return fired;
  }

  /// Advances @p ticks ticks, returning everything that fired across them.
  std::vector<std::uint64_t> advance(std::uint64_t ticks) {
    std::vector<std::uint64_t> fired;
    for (std::uint64_t i = 0; i < ticks; ++i) {
      const std::vector<std::uint64_t> batch = tick();
      fired.insert(fired.end(), batch.begin(), batch.end());
    }
    return fired;
  }

  std::uint64_t now() const { return now_; }
  std::size_t armed() const { return index_.size(); }

 private:
  struct Entry {
    std::uint64_t id;
    std::uint64_t deadline;
  };

  std::uint64_t now_ = 0;
  std::vector<std::vector<Entry>> slots_;
  std::unordered_map<std::uint64_t, std::uint64_t> index_;  // id -> deadline
};

// ------------------------------------------------------------------- TESTS --

namespace {

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

using Ids = std::vector<std::uint64_t>;

Ids sorted(Ids ids) {
  std::sort(ids.begin(), ids.end());
  return ids;
}

bool doTestsPass() {
  bool passed = true;

  {
    TimerWheel wheel(8);
    passed &= expect("arm accepted", wheel.schedule(1, 3));
    passed &= expect("zero delay rejected", !wheel.schedule(2, 0));
    passed &= expect("duplicate id rejected", !wheel.schedule(1, 5));
    passed &= expect("one armed", wheel.armed() == 1);

    passed &= expect("nothing at tick 1", wheel.tick().empty());
    passed &= expect("nothing at tick 2", wheel.tick().empty());
    passed &= expect("fires at tick 3", wheel.tick() == Ids{1});
    passed &= expect("disarmed after firing", wheel.armed() == 0);
    passed &= expect("does not fire twice", wheel.tick().empty());
  }

  // Several timers on the same deadline fire together, in arm order.
  {
    TimerWheel wheel(8);
    wheel.schedule(10, 2);
    wheel.schedule(11, 2);
    wheel.schedule(12, 2);
    passed &=
        expect("batch fires together", wheel.advance(2) == (Ids{10, 11, 12}));
  }

  // Cancellation is the common case for an order gateway.
  {
    TimerWheel wheel(8);
    wheel.schedule(20, 4);
    wheel.schedule(21, 4);
    passed &= expect("cancel armed timer", wheel.cancel(20));
    passed &= expect("cancel is idempotent-safe", !wheel.cancel(20));
    passed &= expect("cancel unknown id", !wheel.cancel(99));
    passed &= expect("one still armed", wheel.armed() == 1);
    passed &= expect("only the live timer fires", wheel.advance(4) == Ids{21});
  }

  // A delay beyond one revolution must not fire early on the aliased slot.
  {
    TimerWheel wheel(4);
    wheel.schedule(30, 6);  // 6 % 4 == 2, so it lands in the slot tick 2 sweeps
    passed &= expect("does not fire on aliased slot", wheel.advance(2).empty());
    passed &= expect("still armed after alias", wheel.armed() == 1);
    passed &= expect("nothing at ticks 3-5", wheel.advance(3).empty());
    passed &= expect("fires on the real deadline", wheel.tick() == Ids{30});
    passed &= expect("clock advanced", wheel.now() == 6);
  }

  // An id may be re-armed once it has fired.
  {
    TimerWheel wheel(4);
    wheel.schedule(40, 1);
    passed &= expect("first firing", wheel.tick() == Ids{40});
    passed &= expect("re-arm after firing", wheel.schedule(40, 2));
    passed &= expect("fires again", wheel.advance(2) == Ids{40});
  }

  // Mixed deadlines across a full wrap.
  {
    TimerWheel wheel(4);
    wheel.schedule(50, 1);
    wheel.schedule(51, 5);
    wheel.schedule(52, 9);
    passed &= expect("staggered firings",
                     sorted(wheel.advance(9)) == (Ids{50, 51, 52}));
    passed &= expect("nothing left armed", wheel.armed() == 0);
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
