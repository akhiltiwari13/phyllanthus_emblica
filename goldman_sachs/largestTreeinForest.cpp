/* @todo: Identify the root of the largest tree in a forest represented as a map
 * of child-parent relationships */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// utility DFS function
// using an adjacency-list representation of the forest. i.e.
// std::unrodered_map<parent,unordered_set<children>>

int getSizeDFS(
    const std::unordered_map<int, std::unordered_set<int>> &adjacenyList,
    int root, std::unordered_set<int> &visited) {
  if (visited.find(root) != visited.end()) {
    return 0;
  } else {
    int count{1};
    visited.insert(root); // mark node as visited.

    // visit all child nodes of the current root
    if (adjacenyList.find(root) != adjacenyList.end()) {

      for (auto &child : adjacenyList.at(root)) {
        count += getSizeDFS(adjacenyList, child, visited);
      }
    }

    return count;
  }
}

/* argument map has {child,parent} pair */
int largestTree(const std::unordered_map<int, int> &immediateParent) {
  /* to return the id of the root of largest tree!! */
  std::unordered_set<int> roots;
  int max_size{0};
  std::unordered_map<int, std::unordered_set<int>> adjacencyList;

  for (auto &itr : immediateParent) {
    adjacencyList[itr.second].insert(itr.first);
  }

  for (auto &itr : immediateParent) {
    roots.insert(itr.second);
  }

  // set of all roots. & create the adjacency list representation.
  for (auto &itr : immediateParent) {
    if (roots.find(itr.first) != roots.end()) {
      roots.erase(itr.first);
    }
  }

  /* dfs the forest to find the size for each root */
  std::unordered_set<int> visited;
  int largestTreeRoot{};
  for (auto root : roots) {
    auto localsize = getSizeDFS(adjacencyList, root, visited);
    largestTreeRoot = max_size < localsize ? root : largestTreeRoot;
    max_size = std::max(max_size, localsize);
  }

  return largestTreeRoot;
}

bool doTestsPass() {
  std::vector<std::pair<std::unordered_map<int, int>, int>> testCases = {
      {{{1, 2}, {2, 3}, {3, 4}}, 4},                // Single tree, 4 nodes
      {{{1, 2}, {2, 3}, {4, 5}}, 3},                // Two trees: one of size 3, another of size 2
      {{{1, 2}, {4, 5}, {5, 6}}, 6},                // Two trees: one of size 2, another of size 3
      {{{1, 2}}, 2},                                // Single tree, 2 nodes
      {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, 2},        // Four separate trees of size 2 each
      {{}, 0},                                      // Empty map, should return 0
      {{{10, 20}, {20, 30}, {30, 40}, {40, 50}, {60, 70}, {70, 80}}, 50},    // One large tree and a smaller one
      {{{1, 10}, {2, 20}, {3, 30}}, 10},             // Three separate trees of size 2 each
      {{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}}, 8}         // Single large tree
  };

  bool passed = true;
  for (unsigned int ii = 0; ii < testCases.size(); ++ii) {
    int actual = largestTree(testCases[ii].first);
    if (actual != testCases[ii].second) {
      passed = false;
      std::cout << "Failed for case" << ii << ", expected "
                << testCases[ii].second << ", actual " << actual << std::endl;
    }
  }
  return passed;
}

int main() {

  /* run the tests. */
  if (doTestsPass()) {
    std::cout << "ALL TESTS PASS." << std::endl;
  } else {
    std::cout << "TESTS FAILED." << std::endl;
  }
  return 0;
}
