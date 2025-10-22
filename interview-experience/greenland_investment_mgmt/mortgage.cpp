/*
- This algorithm could only get 6 out of 15 testcases passing. I am not sure if
this approach is correct however I could not figure out any corner cases for
*/

// int countMaximumDays(std::vector<int> lend, std::vector<int> payback) {
//     int n = lend.size();
//     std::vector<std::pair<int, int>> lenders(n);
//     for (int i = 0; i < n; i++) {
//         lenders[i] = {payback[i], lend[i]};
//     }
//     std::sort(lenders.begin(), lenders.end());

//     int days = 0;
//     int debt = 0;
//     for (const auto& lender : lenders) {
//         if (debt > lender.second) {
//             break;
//         }
//         debt = lender.first;
//         days++;
//     }

//     return days;
// }

// ======================================================
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'countMaximumDays' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY lend
 *  2. INTEGER_ARRAY payback
 */

int countMaximumDays(vector<int> lend, vector<int> payback) {
  int n = lend.size();
  std::vector<std::pair<int, int>> lenders(n);
  for (int i = 0; i < n; i++) {
    lenders[i] = {lend[i], payback[i]};
  }
  std::sort(lenders.begin(), lenders.end());

  int days = 0;
  int debt = 0;
  for (const auto &lender : lenders) {
    if (debt > lender.first) {
      break;
    }
    debt += lender.second - lender.first;
    days++;
  }

  return days;
}

int main() {
  ofstream fout(getenv("OUTPUT_PATH"));

  string lend_count_temp;
  getline(cin, lend_count_temp);

  int lend_count = stoi(ltrim(rtrim(lend_count_temp)));

  vector<int> lend(lend_count);

  for (int i = 0; i < lend_count; i++) {
    string lend_item_temp;
    getline(cin, lend_item_temp);

    int lend_item = stoi(ltrim(rtrim(lend_item_temp)));

    lend[i] = lend_item;
  }

  string payback_count_temp;
  getline(cin, payback_count_temp);

  int payback_count = stoi(ltrim(rtrim(payback_count_temp)));

  vector<int> payback(payback_count);

  for (int i = 0; i < payback_count; i++) {
    string payback_item_temp;
    getline(cin, payback_item_temp);

    int payback_item = stoi(ltrim(rtrim(payback_item_temp)));

    payback[i] = payback_item;
  }

  int result = countMaximumDays(lend, payback);

  fout << result << "\n";

  fout.close();

  return 0;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(), find_if(s.begin(), s.end(), [](char c) {
            return !isspace(static_cast<unsigned char>(c));
          }));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(),
              [](char c) { return !isspace(static_cast<unsigned char>(c)); })
          .base(),
      s.end());

  return s;
}
