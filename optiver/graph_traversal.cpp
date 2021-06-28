#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

/* added header. */
#include <regex>

using namespace std;

namespace app {
class Sol {
public:
  void ParseLine(const string &line, unsigned int lineCount) {
    switch (lineCount) {
    case 0: {
      regex pattern("[\[]([A-Z]),([A-Z]),(\\d+)[\\]]");
      const string delim(" ");
      string::size_type begIdx{}, endIdx{};
      begIdx = line.find_first_not_of(delim);

      while (begIdx != string::npos) {
        endIdx = line.find_first_of(delim, begIdx);

        if (endIdx == string::npos) {
          endIdx = line.length();
        }

        /* process each word. */
        /* report error E1 for input format errors. */
        /* report error E2 for logical input errors. */
        auto pMatch =
            hasProperFormat(line.substr(begIdx, (endIdx - begIdx)), pattern);
        if (pMatch.first) {
          constructGraph(pMatch.second);
        } else {
          cout << "E1" << std::endl;
          exit(0);
        }

        begIdx = line.find_first_not_of(delim, endIdx);
      }

    } break;
    case 1: {
      regex pattern("([A-Z])->([A-Z]),(\\d+)");
      smatch match;
      bool mresult = regex_match(line, match, pattern);
      if (!mresult) {
        cout << "E1" << std::endl;
        exit(0);
      } else {
        /* get start node, destination & max_allowed_time. */
        source = match[1].str()[0];
        destination = match[2].str()[0];
        maxAllowedTime = stoi(match[3].str());

        if (!adjacencyList.count(source) || !adjacencyList.count(destination)) {
          cout << "E2" << std::endl;
          exit(0);
        }
      }
    } break;
    default: {
      /* input should have only 2 lines, else throw Input syntax error and exit.
       */
      cout << "E1" << endl;
      exit(0);
    } break;
    }
  }

  void FindShortestPath() {
      std::cout<<"[DEBUG] executing  FindShortestPath()..."<<std::endl;
    /* auxilary data-structure for finding shortest path using Dijkstras
     * algorithm */
    unordered_map<char, unsigned int> minTime;
    unordered_map<char, char> visitedFrom;
    priority_queue<pair<unsigned int, char>> q;

    /* initializations. */
    q.push(make_pair(0, source));
    for (auto n : adjacencyList) {
      minTime[n.first] = std::numeric_limits<unsigned int>::max();
    }
    minTime[source] = 0;
    visitedFrom[source] = '\0';

    while (!q.empty()) {
      char vert = q.top().second;
      q.pop();

      // visit each neighbour of the node from the adjacency list.
      for (auto edge : adjacencyList[vert]) {
        auto neighbour = edge.first;
        auto wt = edge.second;

        if ((minTime[vert] + wt) < minTime[neighbour]) {
          minTime[neighbour] = minTime[vert] + wt;
          q.push(make_pair(minTime[neighbour], neighbour));
          visitedFrom[neighbour] = vert;
        }
      }
    }

    auto result = minTime[destination];
    cout<<"[DEBUG] minimum time= "<<minTime[destination]<<endl;
    if (result <= maxAllowedTime) {

      std::vector<char> path;

      char nd = destination;
      path.push_back(destination);
      while (nd != source) {
        path.push_back(visitedFrom[nd]);
        nd = visitedFrom[nd];
      }
      reverse(path.begin(), path.end());
      for (auto n : path) {
        cout << n;
        if (n != destination)
          cout << "->";
      }
      std::cout << std::endl;
    } else {
      std::cout << "E3" << std::endl;
    }
  }

  /* Auxilary fuctions for debugging. (not needed for final submission.) */
  void PrintGarph() {
    std::cout << "source: " << source << ", destination: " << destination
              << ", maxAllowedTime: " << maxAllowedTime << std::endl;
    for (auto elem : adjacencyList) {
      std::cout << "[ " << elem.first << "\t ";
      for (auto vals : elem.second) {
        std::cout << "{ " << vals.first << ", " << vals.second << "}";
      }
      std::cout << "] " << std::endl;
    }
  }

private:
  /* using adjacency list for graph representation. */
  unordered_map<char, unordered_map<char, unsigned int>> adjacencyList;
  char source, destination;
  unsigned int maxAllowedTime;

  void out(bool b) { cout << (b ? "found" : "not found") << endl; }

  pair<bool, smatch> hasProperFormat(const string &str, regex &pattern) {

    smatch match;
    bool result = regex_match(str, match, pattern);

    return make_pair(result, match);
  }

  void constructGraph(smatch &match) {
    auto sourceNode = match[1].str()[0];
    auto destinationNode = match[2].str()[0];
    unsigned int weight = stoul(match[3].str());

    if (adjacencyList[sourceNode].count(destinationNode)) {
      cout << "E2" << std::endl;
      exit(0);
    } else {
      adjacencyList[sourceNode].insert(make_pair(destinationNode, weight));
      adjacencyList[destinationNode].insert(make_pair(sourceNode, weight));
    }
  }
};

} // namespace app

int main() {
  freopen("input.txt", "r", stdin);
  app::Sol sol;
  string line{};

  for (int i = 0; i < 2; ++i) {
    getline(cin, line);
    sol.ParseLine(line, i);
  }

  sol.PrintGarph();
  sol.FindShortestPath();
  return 0;
}
