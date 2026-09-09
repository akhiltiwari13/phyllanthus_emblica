/**
 * @file feed_arbitrator.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief PRACTICE — A/B multicast feed arbitration. Target: 30 minutes.
 *
 * An exchange publishes one sequenced stream on two multicast groups, A and B.
 * Both carry every message; either can drop or reorder. Deliver each sequence
 * number exactly once, in order, from whichever line got there first.
 *
 * Sequence numbers start at 1.
 *
 *   vector<uint64_t> onPacket(seq)  packets now deliverable, in order.
 *                                   Empty for a duplicate, or for one that
 *                                   arrived ahead of a gap.
 *   optional<uint64_t> gap()        the seq we are stalled on, if any
 *   vector<uint64_t> skipGap()      give up on the gap (retransmit timed out)
 *                                   and release the buffered backlog
 *   uint64_t expected()             next sequence awaited
 *   size_t buffered()               packets held behind the gap
 *   uint64_t duplicates()           duplicates seen
 *
 * Duplicates are the overwhelmingly common case — both lines carry everything —
 * so make that the cheapest path. A packet arriving early must be held, not
 * dropped and not delivered, and a re-sent copy of a held packet is still a
 * duplicate. When the missing packet finally lands it can unblock an arbitrary
 * run of buffered ones; release them all, in order, in that one call.
 *
 * Run it: the tests below are the spec. Reference in solutions/.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

class FeedArbitrator {
 public:
  std::vector<std::uint64_t> onPacket(std::uint64_t seq) {
    (void)seq;
    return {};  // TODO
  }

  std::optional<std::uint64_t> gap() const { return std::nullopt; }  // TODO

  std::vector<std::uint64_t> skipGap() { return {}; }  // TODO

  std::uint64_t expected() const { return 1; }  // TODO

  std::size_t buffered() const { return 0; }  // TODO

  std::uint64_t duplicates() const { return 0; }  // TODO
};

// ------------------------------------------------------------------- TESTS --

namespace {

bool expect(const char* what, bool condition) {
  if (condition) return true;
  std::cout << "  FAIL " << what << '\n';
  return false;
}

using Seqs = std::vector<std::uint64_t>;

bool doTestsPass() {
  bool passed = true;

  // In-order on line A, every packet duplicated on line B.
  {
    FeedArbitrator arb;
    passed &= expect("first packet delivers", arb.onPacket(1) == Seqs{1});
    passed &= expect("line B duplicate dropped", arb.onPacket(1).empty());
    passed &= expect("second packet delivers", arb.onPacket(2) == Seqs{2});
    passed &= expect("duplicates counted", arb.duplicates() == 1);
    passed &= expect("no gap", !arb.gap().has_value());
  }

  // Line A drops 2; line B supplies it late and unblocks the backlog.
  {
    FeedArbitrator arb;
    passed &= expect("seq 1", arb.onPacket(1) == Seqs{1});
    passed &= expect("seq 3 held", arb.onPacket(3).empty());
    passed &= expect("seq 4 held", arb.onPacket(4).empty());
    passed &= expect("gap reported at 2", arb.gap() == std::uint64_t{2});
    passed &= expect("two buffered", arb.buffered() == 2);

    passed &= expect("late 2 drains 2,3,4", arb.onPacket(2) == (Seqs{2, 3, 4}));
    passed &= expect("gap closed", !arb.gap().has_value());
    passed &= expect("buffer drained", arb.buffered() == 0);
    passed &= expect("expecting 5", arb.expected() == 5);
  }

  // A packet held behind a gap must not be re-held when it repeats.
  {
    FeedArbitrator arb;
    passed &= expect("seq 1", arb.onPacket(1) == Seqs{1});
    passed &= expect("seq 5 held", arb.onPacket(5).empty());
    passed &= expect("seq 5 again held", arb.onPacket(5).empty());
    passed &= expect("held duplicate counted", arb.duplicates() == 1);
    passed &= expect("still one buffered", arb.buffered() == 1);
  }

  // Unrecoverable gap: give up and resume from the backlog.
  {
    FeedArbitrator arb;
    passed &= expect("seq 1", arb.onPacket(1) == Seqs{1});
    passed &= expect("seq 7 held", arb.onPacket(7).empty());
    passed &= expect("seq 8 held", arb.onPacket(8).empty());
    passed &= expect("skip releases 7,8", arb.skipGap() == (Seqs{7, 8}));
    passed &= expect("expecting 9", arb.expected() == 9);
    passed &= expect("skip on clean feed is a no-op", arb.skipGap().empty());
  }

  // Arrival fully reversed — the worst reordering case.
  {
    FeedArbitrator arb;
    passed &= expect("4 held", arb.onPacket(4).empty());
    passed &= expect("3 held", arb.onPacket(3).empty());
    passed &= expect("2 held", arb.onPacket(2).empty());
    passed &=
        expect("1 drains everything", arb.onPacket(1) == (Seqs{1, 2, 3, 4}));
    passed &= expect("expecting 5", arb.expected() == 5);
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
