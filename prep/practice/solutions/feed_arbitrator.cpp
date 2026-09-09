/**
 * @file feed_arbitrator.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference solution — A/B multicast feed arbitration.
 *
 * Exchanges publish the same sequenced stream on two multicast groups. A line
 * handler must emit each sequence number exactly once, in order, taking
 * whichever line delivered it first, and must report a gap only when neither
 * line has filled it.
 *
 * The state is one expected sequence plus a reorder buffer of packets that
 * arrived early. On each accepted packet the buffer is drained forward, so an
 * out-of-order burst costs O(log n) per insert and each packet is emitted once.
 * Duplicates — the common case, since both lines carry everything — are
 * rejected by a single comparison against expected_, which is the cheap path
 * and deliberately the first branch.
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <vector>

class FeedArbitrator {
 public:
  /// Feeds one packet in from either line.
  /// @return the packets now deliverable, in sequence order (may be empty when
  ///         the packet was a duplicate or arrived ahead of a gap).
  std::vector<std::uint64_t> onPacket(std::uint64_t seq) {
    std::vector<std::uint64_t> released;

    if (seq < expected_) {  // already delivered by the other line
      ++duplicates_;
      return released;
    }

    if (seq > expected_) {  // ahead of a gap: hold it, do not deliver yet
      if (!pending_.emplace(seq, true).second) ++duplicates_;
      return released;
    }

    released.push_back(seq);
    ++expected_;

    // The arriving packet may have closed a gap; drain whatever it unblocked.
    auto it = pending_.find(expected_);
    while (it != pending_.end()) {
      released.push_back(expected_);
      pending_.erase(it);
      ++expected_;
      it = pending_.find(expected_);
    }
    return released;
  }

  /// The sequence the feed is stalled on, or nullopt when nothing is buffered.
  std::optional<std::uint64_t> gap() const {
    if (pending_.empty()) return std::nullopt;
    return expected_;
  }

  /// Abandons the outstanding gap — what a real handler does once a
  /// retransmission request times out — and releases the buffered backlog.
  std::vector<std::uint64_t> skipGap() {
    std::vector<std::uint64_t> released;
    if (pending_.empty()) return released;

    expected_ = pending_.begin()->first;
    while (!pending_.empty() && pending_.begin()->first == expected_) {
      released.push_back(expected_);
      pending_.erase(pending_.begin());
      ++expected_;
    }
    return released;
  }

  std::uint64_t expected() const { return expected_; }
  std::size_t buffered() const { return pending_.size(); }
  std::uint64_t duplicates() const { return duplicates_; }

 private:
  std::uint64_t expected_ = 1;  // exchanges conventionally start at 1
  std::uint64_t duplicates_ = 0;
  std::map<std::uint64_t, bool> pending_;
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
