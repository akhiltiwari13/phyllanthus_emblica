#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>


using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMessageStatus' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY timestamps
 *  2. STRING_ARRAY messages
 *  3. INTEGER k
 */

vector<string> getMessageStatus(vector<int> timestamps, vector<string> messages, int k) {
    int n = timestamps.size();
    std::vector<std::string> result(n);
    std::unordered_map<std::string, int> lastTimestamp;

    for (int i = 0; i < n; i++) {
        if (lastTimestamp.count(messages[i]) && timestamps[i] - lastTimestamp[messages[i]] < k) {
            result[i] = "false";
        } else {
            result[i] = "true";
            lastTimestamp[messages[i]] = timestamps[i];
        }
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string timestamps_count_temp;
    getline(cin, timestamps_count_temp);

    int timestamps_count = stoi(ltrim(rtrim(timestamps_count_temp)));

    vector<int> timestamps(timestamps_count);

    for (int i = 0; i < timestamps_count; i++) {
        string timestamps_item_temp;
        getline(cin, timestamps_item_temp);

        int timestamps_item = stoi(ltrim(rtrim(timestamps_item_temp)));

        timestamps[i] = timestamps_item;
    }

    string messages_count_temp;
    getline(cin, messages_count_temp);

    int messages_count = stoi(ltrim(rtrim(messages_count_temp)));

    vector<string> messages(messages_count);

    for (int i = 0; i < messages_count; i++) {
        string messages_item;
        getline(cin, messages_item);

        messages[i] = messages_item;
    }

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    vector<string> result = getMessageStatus(timestamps, messages, k);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];
        cout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
            cout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](char c){return !std::isspace(static_cast<unsigned char>(c));})
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](char c){return !std::isspace(static_cast<unsigned char>(c));}).base(),
        s.end()
    );

    return s;
}
