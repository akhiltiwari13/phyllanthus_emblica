#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>

using namespace std;

bool comp(const pair<string,long>l, const pair<string,long>& r)
{
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
}

void solve(const string &word, unordered_map<string, long>& anagramCache, vector<pair<string,long>>& wordcount){
        std::string sword = word;
        sort(sword.begin(), sword.end());
        if(anagramCache.count(sword))
            anagramCache[sword]=anagramCache[sword]+ 1;
        else
            anagramCache[sword]=1;
        anagramCache[word] = anagramCache[sword];
        wordcount.push_back({word,anagramCache[word]});
}

int main(int argc, char* argv[]) {
    std::string line;
    unordered_map<string, long> anagramCache;
    vector<pair<string,long>> wordcount;  /* for sorting the map based on the value, use a vector<pair<>> instead. */

    /* read lines from input stream, treat ~{alphanumeric} as word separator*/
    while (std::getline(std::cin, line)) {
        std::string word = line;
        string::size_type begIdx, endIdx;
        // search beginning of the first word
        begIdx = line.find_first_not_of(delims);
        // while beginning of a word found
        while (begIdx != string::npos) {
            // search end of the actual word
            endIdx = line.find_first_of (delims, begIdx); if (endIdx == string::npos) {
                // end of word is end of line
                endIdx = line.length();
            }
            // print characters in reverse order
            for (int i=endIdx-1; i>=static_cast<int>(begIdx); --i) { cout << line[i];
            }
            cout << ’ ’;
            // search beginning of the next word
            begIdx = line.find_first_not_of (delims, endIdx); }
        solve(word, anagramCache, wordcount);
        //std::cout << word << ' ' << anagramCache[sword]<<'\n';
    }

    sort(wordcount.begin(),wordcount.end(),comp);
    for(auto itr: wordcount){
        std::cout << itr.first << ' ' << itr.second<<'\n';
    }

    return 0;
}
