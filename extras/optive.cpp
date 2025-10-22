#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'calculate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER ccy_value
 *  2. STRING ccy_pair
 *  3. STRING_ARRAY ccy_rates
 */
/**
100
AUDEUR
6

AUDEUR@0.6216
AUDCNY@4.714
CNYJPY@17.08
EURJPY@129.52
JPYGBP@0.006614
GBPCNY@8.852
*/

using namespace std;

int calculate(int ccy_value, string ccy_pair, vector<string> ccy_rates) {
// first : populate the graph. ccy_rates.
// traverse the graph from base -> quote currency
// compare all the traversal
std::unordered_map<string, std::vector<std::pair<std::string, double>>> cgraph;
for(auto ele: ccy_rates){
    std::string base = ele.substr(0,3);
    std::string quote = ele.substr(3,3);
    auto convrateitr = ele.find_first_of("@");
    double conrate = std::stod(ele.substr(7)); //check substring
    
    cgraph[base].push_back({quote,conrate});
}

// traversal:

auto start = ccy_pair.substr(0,3);
auto end = ccy_pair.substr(3,3);
int result{0};

std::queue<pair<string, double>> q;
q.push({start, 1.0});

std::set<std::string> visited{};

while(!q.empty()){
    //visit while q has members;
    auto [n,e] = q.front(); q.pop();
    //visit it
    
    //check if the quote cur.
    if(n == end){
        //conversion done.
        result = max(result, static_cast<int>(e*ccy_value));
    }
    
    visited.insert(n);
    for(auto neighbour: cgraph[n]){
        if(visited.find(neighbour.first) == visited.end()){
            q.push( std::pair{neighbour.first, (e* (neighbour.second))});
        }
    }
}

return result?result:-1;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));


    string ccy_value_temp;
    getline(cin, ccy_value_temp);

    int ccy_value = stoi(ltrim(rtrim(ccy_value_temp)));

    string ccy_pair;
    getline(cin, ccy_pair);

    string ccy_rates_count_temp;
    getline(cin, ccy_rates_count_temp);

    int ccy_rates_count = stoi(ltrim(rtrim(ccy_rates_count_temp)));

    vector<string> ccy_rates(ccy_rates_count);

    for (int i = 0; i < ccy_rates_count; i++) {
        string ccy_rates_item;
        getline(cin, ccy_rates_item);

        ccy_rates[i] = ccy_rates_item;
    }

    int result = calculate(ccy_value, ccy_pair, ccy_rates);

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


//example
/*1. usd ->(3) inr
2. usd -> (1.5 bhats) 
bht ->(1) inr 

*/
