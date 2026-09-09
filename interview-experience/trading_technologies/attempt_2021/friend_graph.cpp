/**
 * @file friend_graph.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Trading Technologies, 2021 attempt — "can these two be connected?".
 *
 * Friendships form an undirected graph; decide whether two people are in the
 * same connected component. Delivered in TT's Codility harness, so the local
 * `main()` stays behind `#ifndef RunTests` and the given API (`friends`,
 * `addFriendship`, `canBeConnected`) must not be renamed.
 *
 * Two bugs in the original submission, both fixed here:
 *   1. `visited` was a local of `canBeConnected`, so every recursive call
 *      started with an empty set. Because `addFriendship` links both ways
 *      (a<->b), the recursion bounced between neighbours forever and blew the
 *      stack — it never returned a wrong answer, it never returned at all.
 *   2. The loop assigned `rslt = v->canBeConnected(target)` on each iteration,
 *      so a `true` found early was overwritten by a later `false`.
 *
 * Replaced with an iterative BFS over one shared visited set: O(V + E), and no
 * recursion depth to overflow on a large friend graph.
 *
 * @version 0.2
 * @date 2021-06-12
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

class Friend {
 public:
  std::vector<Friend*> friends;

  explicit Friend(std::string email) : email_(std::move(email)) {}

  void addFriendship(Friend* target) {
    friends.push_back(target);
    target->friends.push_back(this);
  }

  const std::string& email() const { return email_; }

  /// Breadth-first search over the friendship graph. The visited set is shared
  /// across the whole traversal, so each person is expanded at most once.
  bool canBeConnected(Friend* target) {
    if (this == target) return true;

    std::unordered_set<const Friend*> visited{this};
    std::queue<Friend*> pending;
    pending.push(this);

    while (!pending.empty()) {
      Friend* current = pending.front();
      pending.pop();

      for (Friend* neighbour : current->friends) {
        if (neighbour == target) return true;
        if (visited.insert(neighbour).second) pending.push(neighbour);
      }
    }
    return false;
  }

 private:
  std::string email_;
};

namespace {

bool expectBool(const char* what, bool actual, bool expected) {
  if (actual == expected) return true;
  std::cout << "  FAIL " << what << ": expected " << std::boolalpha << expected
            << ", got " << actual << '\n';
  return false;
}

bool doTestsPass() {
  bool passed = true;

  //   a -- b -- c
  //        |
  //        d          e (isolated)
  Friend a("a@example.com");
  Friend b("b@example.com");
  Friend c("c@example.com");
  Friend d("d@example.com");
  Friend e("e@example.com");

  a.addFriendship(&b);
  b.addFriendship(&c);
  b.addFriendship(&d);

  passed &= expectBool("self", a.canBeConnected(&a), true);
  passed &= expectBool("direct neighbour", a.canBeConnected(&b), true);
  passed &= expectBool("two hops", a.canBeConnected(&c), true);
  passed &= expectBool("via shared neighbour", c.canBeConnected(&d), true);
  passed &= expectBool("isolated person", a.canBeConnected(&e), false);
  passed &= expectBool("isolated, reversed", e.canBeConnected(&a), false);
  passed &= expectBool("isolated, self", e.canBeConnected(&e), true);

  // A cycle must terminate rather than revisit forever.
  Friend p("p@example.com");
  Friend q("q@example.com");
  Friend r("r@example.com");
  Friend lonely("lonely@example.com");
  p.addFriendship(&q);
  q.addFriendship(&r);
  r.addFriendship(&p);

  passed &= expectBool("cycle, reachable", p.canBeConnected(&r), true);
  passed &= expectBool("cycle, unreachable", p.canBeConnected(&lonely), false);

  if (a.email() != "a@example.com") {
    std::cout << "  FAIL email accessor\n";
    passed = false;
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
