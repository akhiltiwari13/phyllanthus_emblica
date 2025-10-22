/**
 * @file suffixQueries.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief  The ask was for each string str in queries, find the length of (lexicographically) first substring in the given string s. Return the sum of lenghts for all string str in queries.
 * @version 0.1
 * @date 2023-02-06
 * 
 * @copyright akhtiwar (c) 2023
 * 
 */
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<set>
using namespace std;


int suffixQueries(string s, vector<string> queries){
    int result{};
    auto modnum = (int)(pow(10,9)+7);
    std::set<string> lexset;
    for(auto str: queries){
        std::string::size_type idx = 0;
        size_t len = 0;
        while( (idx = s.find(str,idx)) != string::npos){
            len = (s.size()-idx);
            lexset.insert(s.substr(idx));
            idx += str.length();
        }
        len=len?lexset.begin()->length():0;
        result=(result+len)%modnum ;
    }
    return result;
}

int main(){
        std::cout<<suffixQueries("mzadpoghyykhtykg",{"yk"})<<std::endl;
        std::set<string> sset;

        for(auto itr:sset){
            std::cout<<itr<<std::endl;
        }

}