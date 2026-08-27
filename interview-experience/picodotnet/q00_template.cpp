/**
 * @file q00_template.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Reference template for the picodotnet DS & Algo set - copy this file.
 * @version 0.1
 * @date 2026-08-27
 * @copyright Copyright (c) 2026
 *
 * PROBLEM
 *   Maximum subarray sum. Given a sequence of integers, return the largest sum
 *   obtainable from a contiguous, non-empty subarray. An empty input yields 0.
 *   Values may be negative, so the answer is not necessarily positive.
 *
 *   [-2, 1, -3, 4, -1, 2, 1, -5, 4] -> 6   (the subarray [4, -1, 2, 1])
 *
 * APPROACH
 *   brute   : every (start, end) pair, accumulating as we extend the window.
 *             O(n^2) time, O(1) space.
 *   optimal : Kadane - a single left fold carrying (best_so_far, best_ending_here).
 *             O(n) time, O(1) space.
 *   Key insight: a prefix with a negative running sum can never help the suffix
 *   that follows it, so restart the window instead of carrying the deficit.
 */

#include <algorithm>
#include <cstddef>
#include <print>
#include <ranges>
#include <span>
#include <string_view>
#include <utility>
#include <vector>

namespace pico::max_subarray {

/// Brute force - state this one first in the room, then improve on it out loud.
namespace brute {

[[nodiscard]] auto solve(std::span<const int> in) -> long long {
  if (in.empty()) {
    return 0;
  }
  long long best = in.front();
  for (const auto start : std::views::iota(std::size_t{0}, in.size())) {
    long long sum = 0;
    for (const auto end : std::views::iota(start, in.size())) {
      sum += in[end];
      best = std::max(best, sum);
    }
  }
  return best;
}

}  // namespace brute

/// Optimal - what you actually write once the naive version has been narrated.
namespace optimal {

[[nodiscard]] auto solve(std::span<const int> in) -> long long {
  if (in.empty()) {
    return 0;
  }
  // acc.first  = best sum seen anywhere so far
  // acc.second = best sum of a subarray ending at the current element
  using Acc = std::pair<long long, long long>;
  return std::ranges::fold_left(in, Acc{in.front(), 0},
                                [](Acc acc, int value) {
                                  acc.second = std::max(acc.second + value,
                                                        static_cast<long long>(value));
                                  acc.first = std::max(acc.first, acc.second);
                                  return acc;
                                })
      .first;
}

}  // namespace optimal

}  // namespace pico::max_subarray

bool doTestsPass() {
  using namespace pico::max_subarray;

  struct Case {
    std::vector<int> input;
    long long expected;
    std::string_view name;
  };

  const std::vector<Case> cases{
      {{}, 0, "empty"},
      {{7}, 7, "single positive"},
      {{-7}, -7, "single negative"},
      {{-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6, "canonical"},
      {{-5, -2, -9, -1}, -1, "all negative"},
      {{1, 2, 3, 4}, 10, "all positive"},
      {{0, 0, 0}, 0, "all zero"},
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
 *   Trap        : initialising best to 0 instead of the first element - it silently
 *                 returns 0 for an all-negative input, and the usual test cases
 *                 never catch it.
 *   Edge cases  : empty input, single element, all negative, all zero, and overflow
 *                 (n * INT_MAX does not fit in int - hence the long long accumulator).
 *   Follow-ups  : return the indices, not just the sum; handle a streaming input
 *                 where n is unknown; the circular-array variant; the 2-D version;
 *                 make it work on a sliding window of the last k elements.
 *   Pico angle  : the streaming variant is the real one - a feed handler sees each
 *                 tick once and cannot rewind, so O(1) state per element is the
 *                 requirement, not an optimisation.
 */
