//this submission could only clear 6 out of 13 testcases.
#include <bits/stdc++.h>

using namespace std;

bool isAlpha(std::string str){
 bool contains_non_alpha = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") == std::string::npos;   
 return contains_non_alpha;
}

void toUpper(std::string& str){
   for(auto &c: str)c=toupper(c); 
}

void processData(std::stringstream& ss, std::map<string, pair<string,double>>& _map){
    std::string word;
    std::string key{};
    bool isPrice{false};
    while(ss >> word){
        if(isAlpha(word)){
            key = word;
            toUpper(key);
            if(_map.find(key)==_map.end()){
                _map[key] = std::make_pair(word,0.0);
            }
        }else{
            //for numeric data
            if(_map.find(key)!=_map.end()){
                _map[key].second += stod(word);
            }
        }
    }
}

int main(){
    std::string line{}, word{};
    std::map<string, pair<string,double>> _map{};
    //std::stringstream ss;
    while (std::getline(std::cin, line)) {
       std::stringstream ss(line);
       processData(ss, _map);
    }
    
    // print/output the data
    for(auto v: _map){
        std::cout<<v.second.first<<": "<<v.second.second<<std::endl;
    }
        
    return 0;
}
