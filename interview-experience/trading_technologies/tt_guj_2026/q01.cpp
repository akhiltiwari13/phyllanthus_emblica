/**
 * @file q00_template.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Starting point for a timed online-assessment question.
 *
 * Matches the harness Trading Technologies (and Codility generally) uses: the
 * grader compiles with `RunTests` defined and supplies its own main, so keep
 * the local `main()` behind `#ifndef RunTests` and never rename the class or
 * method signatures the question hands you.
 *
 * On test day: copy this file, paste the given skeleton over the SOLUTION
 * block, and fill doTestsPass() with the worked examples from the problem
 * statement *before* writing the implementation — the examples are free test
 * cases and they catch off-by-ones faster than re-reading the code.
 *
 * Checklist before submitting:
 *   - every member initialised (in-class initialiser or ctor init list)
 *   - empty / single-element / all-equal inputs handled
 *   - integer overflow considered on any accumulation
 *   - no allocation in a loop that the problem calls hot
 *   - compiles clean under -Wall -Wextra -Wpedantic -Werror
 *
 * @version 0.1
 * @date 2026-09-09
 * @copyright Copyright (c) 2026
 */

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------- SOLUTION --

class Solution {
 public:
  int solve(const std::vector<int>& input) const {
    (void)input;
    return 0;
  }
};

// ------------------------------------------------------------------- TESTS --

namespace {

template <typename T>
bool expectEq(const char* what, const T& actual, const T& expected) {
  if (actual == expected) return true;
  std::cout << "  FAIL " << what << ": expected " << expected << ", got "
            << actual << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;
  const Solution solution;

  passed &= expectEq("empty input", solution.solve({}), 0);

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
