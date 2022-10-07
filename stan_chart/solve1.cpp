/* @todo: find anagrams */
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
void solve(vector<string> arr, vector<string> vals){
    std::map<string,int> results;

    for(auto pattern: arr){
    std::sort(pattern.begin(), pattern.end());
    if (results.count(pattern)){
            results[pattern]++;
        }
    else{
        results[pattern] = 1;
    }
    }

    for(auto& v: vals){
        std::cout<<v<<": ";
        std::sort(v.begin(), v.end());
        std::cout<< results[v]<<std::endl;

    }

}

int main(int argc, char* argv[]){
    vector<string> sentence{"study", "at", "the", "cat", "god", "act", "tac", "dog", "dusty"};
    vector<string> anagrams{"study", "cat", "god"};

    solve(sentence, anagrams);
return 0;
}
