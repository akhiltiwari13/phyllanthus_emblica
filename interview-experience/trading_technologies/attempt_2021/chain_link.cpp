/**
 * @file chain_link.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Trading Technologies, 2021 attempt — "chain link".
 *
 * Given a link in a doubly-linked chain, report which side of it holds more
 * links. Delivered in TT's Codility harness: the grader defines `RunTests` and
 * supplies its own main, so the local `main()` stays behind `#ifndef RunTests`
 * and the class API (`append`, `longerSide`, `Side`) must not be renamed.
 *
 * Two bugs in the original submission, both fixed here:
 *   1. `left`/`right` were never initialised. `append()` then read
 *      `this->right != NULL` on an indeterminate pointer — undefined behaviour
 *      on the very first call, which is why the graded run misbehaved.
 *   2. `longerSide()` walked leftwards but terminated on `cur != right`,
 *      comparing a left-walking cursor against the right neighbour. That
 *      condition is meaningless; the walk has to stop at the end of the chain.
 *
 * @version 0.2
 * @date 2021-06-12
 * @copyright Copyright (c) 2021
 */

#include <cstddef>
#include <iostream>
#include <stdexcept>

enum Side { NONE, LEFT, RIGHT };

class ChainLink {
 public:
  ChainLink() : left_(nullptr), right_(nullptr) {}

  void append(ChainLink* rightPart) {
    if (right_ != nullptr) throw std::logic_error("Link is already connected.");

    right_ = rightPart;
    rightPart->left_ = this;
  }

  /// Walks both directions independently and compares the hop counts.
  /// O(n) time, O(1) space; NONE when the two sides are equal in length.
  Side longerSide() const {
    std::size_t left_len = 0;
    for (const ChainLink* cur = left_; cur != nullptr; cur = cur->left_)
      ++left_len;

    std::size_t right_len = 0;
    for (const ChainLink* cur = right_; cur != nullptr; cur = cur->right_)
      ++right_len;

    if (left_len == right_len) return Side::NONE;
    return left_len > right_len ? Side::LEFT : Side::RIGHT;
  }

 private:
  ChainLink* left_;
  ChainLink* right_;
};

namespace {

const char* toString(Side side) {
  switch (side) {
    case Side::LEFT:
      return "LEFT";
    case Side::RIGHT:
      return "RIGHT";
    case Side::NONE:
      return "NONE";
  }
  return "?";
}

bool expectSide(const char* what, Side actual, Side expected) {
  if (actual == expected) return true;
  std::cout << "  FAIL " << what << ": expected " << toString(expected)
            << ", got " << toString(actual) << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;

  // A lone link has nothing on either side.
  {
    ChainLink solo;
    passed &= expectSide("solo link", solo.longerSide(), Side::NONE);
  }

  // left -- middle -- right
  {
    ChainLink left, middle, right;
    left.append(&middle);
    middle.append(&right);

    passed &= expectSide("head of 3", left.longerSide(), Side::RIGHT);
    passed &= expectSide("middle of 3", middle.longerSide(), Side::NONE);
    passed &= expectSide("tail of 3", right.longerSide(), Side::LEFT);
  }

  // Lopsided chain: a -- b -- c -- d, asked from b.
  {
    ChainLink a, b, c, d;
    a.append(&b);
    b.append(&c);
    c.append(&d);

    passed &= expectSide("1 left vs 2 right", b.longerSide(), Side::RIGHT);
    passed &= expectSide("2 left vs 1 right", c.longerSide(), Side::LEFT);
  }

  // append() must reject a second right-hand neighbour.
  {
    ChainLink a, b, c;
    a.append(&b);
    bool threw = false;
    try {
      a.append(&c);
    } catch (const std::logic_error&) {
      threw = true;
    }
    if (!threw) {
      std::cout << "  FAIL double append: expected std::logic_error\n";
      passed = false;
    }
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
