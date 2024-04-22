/**
 * author: akhil
 * program iterates through all the input string as and checks if it is malicious
 * Time Complexity O(m*n) where n is the total number of strings and m is the average lenght of the string.
**/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// checks if a string is either palindrome or can be made a palindrome by removing at-most 1 character.
bool isMalicious(string str){
    for(int i=0, j=str.size()-1; i<j; ++i,--j){
        if(str[i] != str[j]){
            auto newstring1 = str.substr(i+1,j-i);
            auto newstring2 = str.substr(i,j-i);
            return equal(newstring1.begin(), newstring1.end(), newstring1.rbegin()) || equal(newstring2.begin(), newstring2.end(), newstring2.rbegin());
        }
    }
    return true;
}


//parse each string and call isMalicious on it.
vector<string> solve(vector<string> passcodes){
    vector<string> results{};

    for(auto str: passcodes){
        if(isMalicious(str))
            results.push_back(str);
    }

    return results;
}

//test code
int main(int argc, char * argv[]){

    vector<string> passcodes{"aba", "abcc", "basdf", "masfg", "yzey", "abcba", "abcbea", "abecbea", "akhilihka", "akhilizhka"};
    std::cout<<"***********entered passcodes: "<<std::endl;
    for(auto str: passcodes){
        std::cout<<str<<std::endl;
    }

    cout<<"solve()"<<endl;
    auto result = solve(passcodes);

    std::cout<<"***********malicious passcodes: "<<std::endl;
    for(auto str: result){
        std::cout<<str<<std::endl;
    }

    return 0;
}

