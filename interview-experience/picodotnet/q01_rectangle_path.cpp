/**
 * @file q01_rectangle_path.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Does a robot's walk trace the perimeter of a rectangle?
 * @version 0.1
 * @date 2026-08-28
 * @copyright Copyright (c) 2026
 *
 * PROBLEM
 *   A robot starts at (0, 0) on an integer grid. A string of moves drives it one
 *   unit at a time: 'U' up, 'D' down, 'L' left, 'R' right. Return true iff the
 *   path it traces is the perimeter of a rectangle, walked exactly once.
 *
 *   "URDL"     -> true   (unit square)
 *   "UURRDDLL" -> true   (2x2 square)
 *   "UUDD"     -> false  (returns to origin, but encloses nothing)
 *   "UUDDLLRR" -> false  (four straight runs, but they reverse, never turn)
 *
 *   Codility hands this over as `bool solution(string &moves)`; the repo
 *   convention of a `std::string_view` in, `bool` out, is the same function.
 *
 * APPROACH
 *   brute   : walk the path recording every unit edge crossed, reject any edge
 *             crossed twice, then demand the edge set be exactly the perimeter
 *             of its own bounding box. Pure geometry, no cleverness.
 *             O(n log n) time, O(n) space.
 *   optimal : collapse the moves into maximal straight runs - the sides - then
 *             assert four of them, adjacent ones perpendicular, and a closed
 *             loop. O(n) time, O(1) space (the run list never exceeds five).
 *   Key insight: a rectangle is not "returns to origin". It is *four sides that
 *   turn*. Two independent facts have to hold - adjacent sides must be
 *   perpendicular (not merely different), and the loop must close. Drop either
 *   and "UUDDLLRR" sneaks through.
 */

#include <algorithm>
#include <cstddef>
#include <print>
#include <set>
#include <string_view>
#include <utility>
#include <vector>

namespace pico::rectangle_path {

/// One grid step. dx/dy read better here than a pair's first/second.
struct Step {
  int dx{};
  int dy{};
};

/// Unit step for a move character; a zero step marks an unrecognised one.
[[nodiscard]] auto decode(char move) -> Step {
  switch (move) {
    case 'U': return {0, 1};
    case 'D': return {0, -1};
    case 'L': return {-1, 0};
    case 'R': return {1, 0};
    default: return {0, 0};
  }
}

[[nodiscard]] auto is_move(Step step) -> bool {
  return step.dx != 0 || step.dy != 0;
}

/// Brute force - state this one first in the room, then improve on it out loud.
namespace brute {

using Point = std::pair<int, int>;
using Edge = std::pair<Point, Point>;

/// Undirected edge, so the two traversal directions collapse to one key.
[[nodiscard]] auto normalise(Point a, Point b) -> Edge {
  return (a < b) ? Edge{a, b} : Edge{b, a};
}

[[nodiscard]] auto solve(std::string_view moves) -> bool {
  Point at{0, 0};
  std::set<Edge> walked;

  for (const char move : moves) {
    const Step step = decode(move);
    if (!is_move(step)) {
      return false;
    }
    const Point next{at.first + step.dx, at.second + step.dy};
    // Re-crossing an edge means the path doubles back; a perimeter never does.
    if (!walked.insert(normalise(at, next)).second) {
      return false;
    }
    at = next;
  }

  if (walked.empty() || at != Point{0, 0}) {
    return false;
  }

  int low_x = 0;
  int high_x = 0;
  int low_y = 0;
  int high_y = 0;
  for (const auto& [from, to] : walked) {
    for (const Point& corner : {from, to}) {
      low_x = std::min(low_x, corner.first);
      high_x = std::max(high_x, corner.first);
      low_y = std::min(low_y, corner.second);
      high_y = std::max(high_y, corner.second);
    }
  }
  if (low_x == high_x || low_y == high_y) {
    return false;  // degenerate: a line encloses no area
  }

  // Every unit edge on the boundary of the bounding box, and nothing else.
  std::set<Edge> perimeter;
  for (int x = low_x; x < high_x; ++x) {
    perimeter.insert(normalise({x, low_y}, {x + 1, low_y}));
    perimeter.insert(normalise({x, high_y}, {x + 1, high_y}));
  }
  for (int y = low_y; y < high_y; ++y) {
    perimeter.insert(normalise({low_x, y}, {low_x, y + 1}));
    perimeter.insert(normalise({high_x, y}, {high_x, y + 1}));
  }
  return walked == perimeter;
}

}  // namespace brute

/// Optimal - what you actually write once the naive version has been narrated.
namespace optimal {

[[nodiscard]] auto is_vertical(char move) -> bool {
  return move == 'U' || move == 'D';
}

[[nodiscard]] auto solve(std::string_view moves) -> bool {
  // Each entry is one maximal straight run: the direction and how far it went.
  std::vector<std::pair<char, int>> sides;

  for (const char move : moves) {
    if (!is_move(decode(move))) {
      return false;
    }
    if (!sides.empty() && sides.back().first == move) {
      ++sides.back().second;
    } else if (sides.size() < 5) {
      // Four sides, plus one more if the walk began mid-side and the tail
      // wraps back into the head. Anything beyond that can never fold to four.
      sides.emplace_back(move, 1);
    } else {
      return false;
    }
  }

  // A closed path that started mid-side split that side across the two ends.
  if (sides.size() == 5 && sides.front().first == sides.back().first) {
    sides.front().second += sides.back().second;
    sides.pop_back();
  }
  if (sides.size() != 4) {
    return false;  // also rejects the empty walk
  }

  int x = 0;
  int y = 0;
  for (std::size_t i = 0; i < sides.size(); ++i) {
    // Adjacent sides must turn, not reverse. Without this "UUDDLLRR" passes:
    // four runs, net displacement zero, yet it is a line walked twice.
    if (is_vertical(sides[i].first) ==
        is_vertical(sides[(i + 1) % sides.size()].first)) {
      return false;
    }
    const Step step = decode(sides[i].first);
    x += step.dx * sides[i].second;
    y += step.dy * sides[i].second;
  }
  // Closing the loop is what forces opposite sides to be equal in length.
  return x == 0 && y == 0;
}

}  // namespace optimal

}  // namespace pico::rectangle_path

bool doTestsPass() {
  using namespace pico::rectangle_path;

  struct Case {
    std::string_view input;
    bool expected;
    std::string_view name;
  };

  const std::vector<Case> cases{
      {"URDL", true, "unit square"},
      {"RULD", true, "unit square, other winding"},
      {"UURRDDLL", true, "2x2 square"},
      {"RRUULLDD", true, "same square, opposite winding"},
      {"UUURDDDL", true, "3x1 rectangle"},
      {"LLDDRRUU", true, "starts at a different corner"},
      {"URRDDLLU", true, "starts mid-side; tail wraps into the head"},
      {"", false, "empty walk"},
      {"U", false, "single move"},
      {"UD", false, "out and back"},
      {"UUDD", false, "out and back, longer"},
      {"UUDDLLRR", false, "four runs, but sides reverse instead of turning"},
      {"UURRDDL", false, "does not close"},
      {"URD", false, "only three sides"},
      {"URDLU", false, "square plus a tail"},
      {"URDLURDL", false, "square walked twice"},
      {"UUURRRDDDLL", false, "unequal opposite sides"},
      {"UUXRRDDLL", false, "unrecognised character"},
      {"urdl", false, "lowercase is not in the alphabet"},
  };

  bool passed = true;
  for (const auto& [input, expected, name] : cases) {
    // Cross-check both implementations against the expectation - this is what
    // makes keeping the naive version around worth the extra lines.
    for (const auto& [label, actual] :
         {std::pair{"brute", brute::solve(input)},
          std::pair{"optimal", optimal::solve(input)}}) {
      if (actual != expected) {
        passed = false;
        std::println("FAILED [{}] {}: input \"{}\", expected {}, actual {}", label,
                     name, input, expected, actual);
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
 *   Trap        : solving "returns to origin" instead of "forms a rectangle".
 *                 Counting U==D && L==R is a different, much easier problem and
 *                 passes "UUDD". Pin the definition down before writing code.
 *   Trap        : checking that adjacent runs *differ* rather than that they are
 *                 *perpendicular*. Run-collapsing already guarantees they differ,
 *                 so the weaker test is free and wrong - "UUDDLLRR" walks it in.
 *   Edge cases  : empty string, a single move, a walk that closes but encloses
 *                 nothing, the square walked twice, unrecognised characters, and
 *                 the walk that starts mid-side so its last run wraps into its
 *                 first ("URRDDLLU").
 *   Judgement   : "URRDDLLU" is accepted here - geometrically it is a rectangle.
 *                 If the grader insists the walk begin at a corner, delete the
 *                 wrap-merge and it becomes false. Say which one you assumed.
 *   Follow-ups  : return the rectangle's area or corners; allow diagonal moves;
 *                 accept any simple rectilinear polygon, not just rectangles;
 *                 detect self-intersection in an arbitrary walk (the brute-force
 *                 edge set already does this, which is why it is worth keeping).
 *   Pico angle  : the run-length collapse is the same trick as compressing a
 *                 tick stream into runs of unchanged state - you scan once and
 *                 keep O(1) state, rather than materialising the whole path.
 */
