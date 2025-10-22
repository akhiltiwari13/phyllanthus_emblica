// #include <bits/stdc++.h>
#include <cctype>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMinMachines' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY start
 *  2. INTEGER_ARRAY end
 */

int getMinMachines(vector<int> start, vector<int> end) {
    //reformat the input for better parsing
    std::vector<std::pair<int, int>> tasks;
    for (int i = 0; i < static_cast<int>(start.size()); i++) {
        tasks.push_back({start[i], end[i]});
    }
    
    //sort in ascending orders of start time.
    std::sort(tasks.begin(), tasks.end());
    
    std::priority_queue<int, std::vector<int>, std::greater<int>> machineQueue;
    for (const auto& task : tasks) {
        if (!machineQueue.empty() && machineQueue.top() < task.first) {
            machineQueue.pop();
        }
        machineQueue.push(task.second);
    }
    return machineQueue.size();
}
void printHelp() {
    std::cout << "Usage: ./program_name" << std::endl;
    std::cout << "This program calculates the minimum number of machines needed to complete a set of tasks." << std::endl;
    std::cout << "Input format:" << std::endl;
    std::cout << "  First line: Number of tasks (n)" << std::endl;
    std::cout << "  Next n lines: Start times of tasks" << std::endl;
    std::cout << "  Next line: Number of tasks (should be same as n)" << std::endl;
    std::cout << "  Next n lines: End times of tasks" << std::endl;
    std::cout << "Output:" << std::endl;
    std::cout << "  Minimum number of machines required" << std::endl;
}

int main()
{
    printHelp();
    ofstream fout(getenv("OUTPUT_PATH"));

    string start_count_temp;
    getline(cin, start_count_temp);

    int start_count = stoi(ltrim(rtrim(start_count_temp)));

    vector<int> start(start_count);

    for (int i = 0; i < start_count; i++) {
        string start_item_temp;
        getline(cin, start_item_temp);

        int start_item = stoi(ltrim(rtrim(start_item_temp)));

        start[i] = start_item;
    }

    string end_count_temp;
    getline(cin, end_count_temp);

    int end_count = stoi(ltrim(rtrim(end_count_temp)));

    vector<int> end(end_count);

    for (int i = 0; i < end_count; i++) {
        string end_item_temp;
        getline(cin, end_item_temp);

        int end_item = stoi(ltrim(rtrim(end_item_temp)));

        end[i] = end_item;
    }

    int result = getMinMachines(start, end);

    fout << result << "\n";
    std::cout << "minimum machines:" << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        // find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
        find_if(s.begin(), s.end(), [](char c){ return ! std::isspace(static_cast<unsigned char>(c));})
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](char c){ return !std::isspace(static_cast<unsigned char>(c));}).base(),
        s.end()
    );

    return s;
}
