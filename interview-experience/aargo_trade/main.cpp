#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'itemsSort' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY items as parameter.
 */

bool sortFunc(pair<int, int> p1, pair<int, int> p2) {
  if (p1.second == p2.second) {
    return p1.first < p2.first;
  }
  return p1.second < p2.second;
}

vector<int> itemsSort(vector<int> items) {
  unordered_map<int, size_t> cache;
  vector<pair<int, int>> freqVec;
  for (auto itr : items) {
    cache[itr]++;
}
for(auto itr : cache) {
    freqVec.push_back({itr.first, itr.second});
}

sort(freqVec.begin(), freqVec.end(), sortFunc);
vector<int> sortedArr;
for(auto it : freqVec) {
    for(int i=0; i<it.second; i++) {
        sortedArr.push_back(it.first);
    }
}

return sortedArr;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string items_count_temp;
    getline(cin, items_count_temp);

    int items_count = stoi(ltrim(rtrim(items_count_temp)));

    vector<int> items(items_count);

    for (int i = 0; i < items_count; i++) {
        string items_item_temp;
        getline(cin, items_item_temp);

        int items_item = stoi(ltrim(rtrim(items_item_temp)));

        items[i] = items_item;
    }

    vector<int> result = itemsSort(items);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

//ptr_fun is not defined for mac os env.
// string ltrim(const string &str) {
//     string s(str);

//     s.erase(
//         s.begin(),
//         find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
//     );

//     return s;
// }

// string rtrim(const string &str) {
//     string s(str);

//     s.erase(
//         find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
//         s.end()
//     );

//     return s;
// }

string ltrim(const string& str) {
    string s(str);
    s.erase(s.begin(), find_if(s.begin(), s.end(),
        [](int c) {
            return !isspace(c);
        }
    ));
    return s;
}

string rtrim(const string& str) {
    string s(str);
    s.erase(find_if(s.rbegin(), s.rend(),
        [](int c) {
            return !isspace(c);
        }
    ).base(), s.end());
    return s;
}

