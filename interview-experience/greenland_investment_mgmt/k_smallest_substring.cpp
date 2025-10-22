 // const auto n = input_str.size();
 //    auto min_length = n + 1;
 //    std::string result;
 //
 //    for (const auto& [left, _] : input_str | std::views::enumerate) {
 //        int count_ones = 0;
 //        for (const auto& [right, ch] : input_str.substr(left) | std::views::enumerate) {
 //            count_ones += (ch == '1');
 //            if (count_ones == k) {
 //                const auto current_length = right + 1;
 //                auto current_substring = input_str.substr(left, current_length);
 //                
 //                if (current_length < min_length || 
 //                    (current_length == min_length && current_substring < result)) {
 //                    min_length = current_length;
 //                    result = current_substring;
 //                }
 //                break;  // No need to check longer substrings starting from 'left'
 //            }
 //        }
 //    }
 //
 //    return result;
 //
 #include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getSubstring' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING input_str
 *  2. INTEGER k
 */

string getSubstring(string input_str, int k) {
    
    //attempt 2
    int n = input_str.size();
    int min_length = n + 1;
    string result;
    
    for (int left = 0; left < n; ++left) {
        int count_ones = 0;
        for (int right = left; right < n; ++right) {
            if (input_str[right] == '1') {
                count_ones++;
            }
            if (count_ones == k) {
                int current_length = right - left + 1;
                string current_substring = input_str.substr(left, current_length);
                
                if (current_length < min_length) {
                    min_length = current_length;
                    result = current_substring;
                } else if (current_length == min_length && current_substring < result) {
                    result = current_substring;
                }
                break;
            }
        }
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string input_str;
    getline(cin, input_str);

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    string result = getSubstring(input_str, k);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

