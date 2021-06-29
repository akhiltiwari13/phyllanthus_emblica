#include <cstdio>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
typedef tuple<unsigned int, unsigned int, unsigned int> edge;

void FloydWarshall(vector<vector<unsigned int>> &distance_matrix,
                   unsigned int num_city) {
  /* taking each node as a 'via' node. */
  for (unsigned int via = 0; via < num_city; ++via) {
    for (unsigned int i = 0; i < num_city; ++i) {
      for (unsigned int j = 0; j < num_city; ++j) {
        /* check if a path exists between i & j through the via node! */
        if ((distance_matrix[i][via] != numeric_limits<unsigned int>::max()) &&
            (distance_matrix[j][via] != numeric_limits<unsigned int>::max())) {
          distance_matrix[i][j] =
              min(distance_matrix[i][j],
                  (distance_matrix[i][via] + distance_matrix[j][via]));
        }
      }
    }
  }

  cout << "[DEBUG] After Floyd Warshall on Adjacency matrix.." << std::endl;
  cout << "[" << endl;
  for (auto itr : distance_matrix) {
    cout << "[\t ";
    for (auto dist : itr) {
      cout << dist << " ";
    }
    cout << "\t]" << endl;
  }
  cout << "]";
}

edge ProposalQuantifier(const set<edge> &road_edge_list,
                        const set<edge> &proposal_edge_list,
                        unsigned int num_city) {
  edge best_proposal;

  /* create an adjacency matrix to run Floyd-Warshall's algorithm on. */
  vector<vector<unsigned int>> distance_matrix(
      num_city,
      vector<unsigned int>(num_city, numeric_limits<unsigned int>::max()));

  /* make diagonal elements of adjacency matrix as 0; */
  for (unsigned int i = 0; i < num_city; ++i) {
    distance_matrix[i][i] = 0;
  }

  for (auto road : road_edge_list) {
    distance_matrix[get<0>(road)][get<1>(road)] =
        distance_matrix[get<1>(road)][get<0>(road)] = get<2>(road);
  }

  cout << "[DEBUG] Adjacency matrix.." << std::endl;
  cout << "[" << endl;
  for (auto itr : distance_matrix) {
    cout << "[\t ";
    for (auto dist : itr) {
      cout << dist << " ";
    }
    cout << "\t]" << endl;
  }
  cout << "] ";

  FloydWarshall(distance_matrix, num_city);

  return best_proposal;
}

int main() {
  vector<string> input_files{"rn_input1.txt", "rn_input2.txt"};

  for (auto file : input_files) {

    set<edge> road_edge_list;
    set<edge> proposal_edge_list;

    /* varaibles to store inputs. */
    unsigned int num_city{}, num_road{}, num_proposals{};
    unsigned int city_s{}, city_d{}, distance{};

    /* edge highway; */
    freopen(file.c_str(), "r", stdin);
    cin >> num_city >> num_road >> num_proposals;

    for (unsigned int i = 0; i < num_road; ++i) {
      cin >> city_s;
      cin >> city_d;
      cin >> distance;

      road_edge_list.insert(make_tuple(city_s, city_d, distance));
    }

    for (unsigned int i = 0; i < num_proposals; ++i) {
      cin >> city_s;
      cin >> city_d;
      cin >> distance;

      proposal_edge_list.insert(make_tuple(city_s, city_d, distance));
    }

    /* print roads and proposals */
    cout << "[DEBUG] road list:" << endl;
    for (auto roads : road_edge_list) {
      cout << "{" << get<0>(roads) << ", " << get<1>(roads) << ", "
           << get<2>(roads) << "}" << endl;
    }
    cout << "[DEBUG] proposal list:" << endl;
    for (auto prop : proposal_edge_list) {
      cout << "{" << get<0>(prop) << ", " << get<1>(prop) << ", "
           << get<2>(prop) << "}" << endl;
    }

    auto best_proposal =
        ProposalQuantifier(road_edge_list, proposal_edge_list, num_city);
    cout << "[INFO] best proposal:" << endl;
    cout << "{" << get<0>(best_proposal) << ", " << get<1>(best_proposal)
         << ", " << get<2>(best_proposal) << "}" << endl;
  }

  return 0;
}
