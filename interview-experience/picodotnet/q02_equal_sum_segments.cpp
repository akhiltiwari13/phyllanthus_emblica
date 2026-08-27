/**
 * @file q02_equal_sum_segments.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Most disjoint adjacent pairs that all share one sum.
 * @version 0.1
 * @date 2026-08-28
 * @copyright Copyright (c) 2026
 *
 * PROBLEM
 *   Given an array A, a segment of length 2 is an adjacent pair (A[i], A[i+1]),
 *   identified by its start index i. Two segments are non-intersecting when they
 *   share no index, i.e. their starts differ by at least 2. Return the largest
 *   number of pairwise non-intersecting segments whose sums are all equal.
 *
 *   [10, 1, 3, 1, 2, 2, 1, 0, 4] -> 3
 *       sum 4 occurs at starts 1, 2, 4, 7; starts 1, 4 and 7 are disjoint.
 *
 * APPROACH
 *   brute   : collect the distinct pair sums, and for each one sweep the array
 *             greedily taking any candidate that clears the last one taken.
 *             O(n^2) time, O(n) space - and it times out on the large tests.
 *   optimal : the same greedy, but all sums run at once. Bucket each start by
 *             its pair sum and keep (count, last start taken) per bucket; one
 *             sweep advances every bucket. O(n) time, O(n) space.
 *   Key insight: segments with different sums can never block one another, so
 *   the per-sum greedies are independent. Interleaving them costs nothing -
 *   each index is still touched once - which is what removes the outer loop.
 */

#include <algorithm>
#include <cstddef>
#include <print>
#include <span>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace pico::equal_sum_segments {

/// Sum of the pair starting at `start`; widened because int + int can overflow.
[[nodiscard]] auto pair_sum(std::span<const int> in, std::size_t start) -> long long {
  return static_cast<long long>(in[start]) + in[start + 1];
}

/// Brute force - state this one first in the room, then improve on it out loud.
namespace brute {

[[nodiscard]] auto solve(std::span<const int> in) -> int {
  if (in.size() < 2) {
    return 0;
  }
  const std::size_t starts = in.size() - 1;

  std::vector<long long> sums;
  sums.reserve(starts);
  for (std::size_t i = 0; i < starts; ++i) {
    sums.push_back(pair_sum(in, i));
  }
  std::ranges::sort(sums);
  const auto duplicates = std::ranges::unique(sums);
  sums.erase(duplicates.begin(), duplicates.end());

  int best = 0;
  for (const long long target : sums) {
    int count = 0;
    // -2 lets the first candidate through: i >= -2 + 2 == 0 always holds.
    int last_start = -2;
    for (std::size_t i = 0; i < starts; ++i) {
      if (pair_sum(in, i) == target && static_cast<int>(i) >= last_start + 2) {
        ++count;
        last_start = static_cast<int>(i);
      }
    }
    best = std::max(best, count);
  }
  return best;
}

}  // namespace brute

/// Optimal - what you actually write once the naive version has been narrated.
namespace optimal {

[[nodiscard]] auto solve(std::span<const int> in) -> int {
  if (in.size() < 2) {
    return 0;
  }

  /// Per candidate sum: segments taken so far, and where the last one started.
  struct Progress {
    int count{};
    int last_start{-2};
  };
  std::unordered_map<long long, Progress> by_sum;
  by_sum.reserve(in.size() * 2);

  int best = 0;
  for (std::size_t i = 0; i + 1 < in.size(); ++i) {
    Progress& run = by_sum.try_emplace(pair_sum(in, i), Progress{}).first->second;

    // Earliest-first is optimal: every segment is the same width, so taking the
    // leftmost candidate never blocks more than a later choice would.
    if (static_cast<int>(i) >= run.last_start + 2) {
      ++run.count;
      run.last_start = static_cast<int>(i);
      best = std::max(best, run.count);
    }
  }
  return best;
}

}  // namespace optimal

}  // namespace pico::equal_sum_segments

bool doTestsPass() {
  using namespace pico::equal_sum_segments;

  struct Case {
    std::vector<int> input;
    int expected;
    std::string_view name;
  };

  const std::vector<Case> cases{
      {{}, 0, "empty"},
      {{5}, 0, "single element, no segment fits"},
      {{1, 2}, 1, "exactly one segment"},
      {{1, 1, 1}, 1, "overlapping candidates, only one fits"},
      {{1, 1, 1, 1}, 2, "sum 2 at starts 0,1,2 -> take 0 and 2"},
      {{10, 1, 3, 1, 2, 2, 1, 0, 4}, 3, "canonical: sum 4 at starts 1,4,7"},
      {{1, 2, 1, 2, 1, 2}, 3, "sum 3 at every start -> take 0,2,4"},
      {{1, 3, 2, 2, 3, 1}, 3, "sum 4 at starts 0,2,4 beats sum 5"},
      {{1, 2, 3, 4, 5}, 1, "all sums distinct"},
      {{-1, 1, -1, 1}, 2, "negatives, sum 0"},
      {{0, 0, 0, 0, 0, 0}, 3, "all zeros"},
      {{2147483647, 2147483647, 2147483647, 2147483647}, 2, "int sum would overflow"},
      {{-2147483648, -2147483648, -2147483648, -2147483648}, 2, "negative overflow"},
      {{5, 1, 4, 2, 3, 3, 2, 4}, 4, "sum 6 at every start -> take 0,2,4,6"},
  };

  bool passed = true;
  for (const auto& [input, expected, name] : cases) {
    // Cross-check both implementations against the expectation - this is what
    // makes keeping the naive version around worth the extra lines.
    for (const auto& [label, actual] : {std::pair{"brute", brute::solve(input)},
                                        std::pair{"optimal", optimal::solve(input)}}) {
      if (actual != expected) {
        passed = false;
        std::println("FAILED [{}] {}: expected {}, actual {}", label, name, expected,
                     actual);
      }
    }
  }
  return passed;
}

int main() {
  std::println("{}", doTestsPass() ? "ALL TESTS PASS." : "TESTS FAILED.");
  return 0;
}

/**
 * INTERVIEW NOTES
 *   Trap        : the O(n^2) shape is easy to reach and easy to stop at - "for
 *                 each distinct sum, sweep the array". Inverting the loops so
 *                 one sweep advances every sum is the whole question.
 *   Trap        : A[i] + A[i+1] overflows int for large operands. The sum is only
 *                 ever a key, so widening to long long costs nothing.
 *   Trap        : counting the most frequent sum instead of running the greedy.
 *                 That answers the problem without the disjointness rule and is
 *                 wrong for [1,1,1] (frequency 2, but only one segment fits).
 *   Edge cases  : n < 2, all elements equal, all sums distinct, negatives, and
 *                 overlapping candidates where greedy has to skip one.
 *   Why greedy  : all segments are the same width, so earliest-first leaves a
 *                 suffix that is a superset of what any other pick leaves. This
 *                 is interval scheduling; say the name and move on.
 *   Follow-ups  : segments of length k, not 2; return the chosen indices; allow
 *                 segments to touch (the disjointness rule vanishes and the
 *                 answer collapses to the most frequent sum); maximise total
 *                 covered length rather than segment count (that one needs DP).
 *   Pico angle  : the bucketed single sweep is the standard shape for keying a
 *                 stream by symbol - per-key state in a hash map, one pass, no
 *                 rewind. Same skeleton as a per-instrument aggregator.
 */
