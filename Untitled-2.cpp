#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'getMaxProfit' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY pnl
 *  2. INTEGER k
 */

long getMaxProfit(vector<int> pnl, int k) {
    long long result = 0;
    sort(pnl.begin(), pnl.end(), greater<int>());
    //std::accumulate(pnl.begin(), pnl.end()-k,result);
    for(int i=0; i<pnl.size() && k>0; ++i  ){
        //result += pnl[i]>0?pnl[i]:0;
        if(pnl[i]>=0){
            result += pnl[i];
        }else{
            if(k==0 ) return -1;
            --k;
            result += pnl[i];
        }
    }
    if(k)return -1;else return result>=0?result:-1;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string pnl_count_temp;
   getline(cin, pnl_count_temp);

    int pnl_count = stoi(ltrim(rtrim(pnl_count_temp)));

    vector<int> pnl(pnl_count);

    for (int i = 0; i < pnl_count; i++) {
        string pnl_item_temp;
        getline(cin, pnl_item_temp);

        int pnl_item = stoi(ltrim(rtrim(pnl_item_temp)));

        pnl[i] = pnl_item;
    }

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    long result = getMaxProfit(pnl, k);

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

