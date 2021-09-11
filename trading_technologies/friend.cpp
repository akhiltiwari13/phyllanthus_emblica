#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

class Friend {
public:
  std::vector<Friend *> friends;

  Friend(std::string email) { this->email = email; }

  void addFriendship(Friend *target) {
    friends.push_back(target);
    target->friends.push_back(this);
  }

  bool canBeConnected(Friend *target) {
    bool rslt = false;
    if (this == target) {
      return true;
    } else if (this->isNeighbour(target))
      return true;
    else {
      std::unordered_set<Friend *> visited;
      visited.emplace(this);
      for (auto v : this->friends) {
        if (visited.count(v))
          continue;
        visited.emplace(v);
        rslt = v->canBeConnected(target);
      }
      return rslt;
    }
  }

private:
  std::string email;
  bool isNeighbour(Friend *target) {
    if (std::find(begin(friends), end(friends), target) != end(friends))
      return true;
    return false;
  }
};

#ifndef RunTests
int main() {
  Friend a("A");
  Friend b("B");
  Friend c("C");
  Friend d("D");
  Friend e("E");

  a.addFriendship(&b);
  b.addFriendship(&c);
  b.addFriendship(&d);
  /* e.addFriendship(&c); */

  std::cout << a.canBeConnected(&e);
}
#endif
