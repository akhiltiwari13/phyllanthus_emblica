#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

string trim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'totalLiquidFilled' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */

long long totalLiquidFilled(vector<vector<int>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    long long totalLiquid = 0;

    vector<vector<int>> leftMax(rows, vector<int>(cols, 0));
    vector<vector<int>> rightMax(rows, vector<int>(cols, 0));
    vector<vector<int>> topMax(rows, vector<int>(cols, 0));
    vector<vector<int>> bottomMax(rows, vector<int>(cols, 0));

    if (matrix.empty() || matrix[0].empty()) return 0;
    // Calculate max heights from all four directions
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == 0) leftMax[i][j] = matrix[i][j];
            else leftMax[i][j] = max(leftMax[i][j - 1], matrix[i][j]);

            if (i == 0) topMax[i][j] = matrix[i][j];
            else topMax[i][j] = max(topMax[i - 1][j], matrix[i][j]);
        }
    }

    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (j == cols - 1) rightMax[i][j] = matrix[i][j];
            else rightMax[i][j] = max(rightMax[i][j + 1], matrix[i][j]);

            if (i == rows - 1) bottomMax[i][j] = matrix[i][j];
            else bottomMax[i][j] = max(bottomMax[i + 1][j], matrix[i][j]);
        }
    }

    // Calculate total liquid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int minHeight = min({leftMax[i][j], rightMax[i][j], topMax[i][j], bottomMax[i][j]});
            totalLiquid += max(0, minHeight - matrix[i][j]);
        }
    }
    
    //logging
/*    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        cout << "LeftMax: " << leftMax[i][j] << ", RightMax: " << rightMax[i][j]
             << ", TopMax: " << topMax[i][j] << ", BottomMax: " << bottomMax[i][j] << endl;
    }
}
cout<<"totoalLiquid:"<<totalLiquid<<std::endl;*/

    return totalLiquid;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string matrix_rows_temp;
    getline(cin, matrix_rows_temp);

    int matrix_rows = stoi(trim(matrix_rows_temp));

    string matrix_columns_temp;
    getline(cin, matrix_columns_temp);

    int matrix_columns = stoi(trim(matrix_columns_temp));

    vector<vector<int>> matrix(matrix_rows);

    for (int i = 0; i < matrix_rows; i++) {
        matrix[i].resize(matrix_columns);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(trim(matrix_row_temp_temp));

        for (int j = 0; j < matrix_columns; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    int result = totalLiquidFilled(matrix);

    fout << result << "\n";

    fout.close();

    return 0;
}

std::string trim(const std::string& s) {
    auto is_not_space = [](unsigned char c) { return !std::isspace(c); };

    auto first = std::find_if(s.begin(), s.end(), is_not_space);
    auto last = std::find_if(s.rbegin(), s.rend(), is_not_space).base();

    return (first < last) ? std::string(first, last) : std::string();
}

// string ltrim(const string &str) {
//     string s(str);
//
//     s.erase(
//         s.begin(),
//         find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
//     );
//
//     return s;
// }
//
// string rtrim(const string &str) {
//     string s(str);
//
//     s.erase(
//         find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
//         s.end()
//     );
//
//     return s;
// }
//
vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

