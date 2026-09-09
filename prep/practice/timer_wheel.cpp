/**
 * @file timer_wheel.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief PRACTICE — single-level timing wheel. Target: 35 minutes.
 *
 * An order gateway arms a timeout for every in-flight order and cancels almost
 * all of them when the ack comes back. A priority_queue makes arm and cancel
 * O(log n); a timing wheel makes both O(1). Build the wheel.
 *
 *   TimerWheel(slots)                a wheel of `slots` buckets
 *   bool schedule(id, delay)         fire `id` `delay` ticks from now.
 *                                    Reject delay 0 or an already-armed id.
 *   bool cancel(id)                  disarm; false if not armed
 *   vector<uint64_t> tick()          advance one tick, return what fired
 *   vector<uint64_t> advance(n)      n ticks; everything that fired across them
 *   uint64_t now() / size_t armed()
 *
 * Bucket a timer by `deadline % slots` so a tick only ever inspects one bucket.
 * Two things follow that are easy to miss:
 *   - a delay longer than one full revolution aliases onto a slot the wheel
 *     reaches too early. It must not fire then. Carry it.
 *   - cancel() is the hot path and must not walk a bucket's list. Work out what
 *     it can do instead, and who cleans up afterwards.
 * An id that has already fired may be armed again.
 *
 * Run it: the tests below are the spec. Reference in solutions/.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

class TimerWheel {
 public:
  explicit TimerWheel(std::size_t slots) { (void)slots; }  // TODO

  bool schedule(std::uint64_t id, std::uint64_t delay) {
    (void)id, (void)delay;
    return false;  // TODO
  }

  bool cancel(std::uint64_t id) {
    (void)id;
    return false;  // TODO
  }

  std::vector<std::uint64_t> tick() { return {}; }  // TODO

  std::vector<std::uint64_t> advance(std::uint64_t ticks) {
    (void)ticks;
    return {};  // TODO
  }

  std::uint64_t now() const { return 0; }  // TODO

  std::size_t armed() const { return 0; }  // TODO
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
