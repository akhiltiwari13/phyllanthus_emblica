/*
task is to write a function that, given a list of words and a string, finds and returns the word in the list that is scrambled up inside the string, if any exists. There will be at most one matching word. The letters don't need to be in order or next to each other. The letters cannot be reused.
Example:
words = ['cat', 'baby', 'dog', 'bird', 'car', 'ax']
string1 = 'tcabnihjs' -> cat 
string2 = 'brhahyrbaz' -> baby 
string3 = 'test' -> Null/None 
find_embedded_word(words, string1) -> cat (the letters do not have to be in order)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<string> find_embedded_word(vector<string>& words, string& phrase){
 vector<string> result{};   
 auto tphrase(phrase);
 for(auto w: words){
    //std::cout<<w<<"\t";
    bool found = true;
    for(auto ch:w){
      //std::cout<<"finding:"<<ch<<"\t";
      if(tphrase.find(ch) == string::npos){
        found=false;
      }
      else{
        tphrase.erase(tphrase.find(ch));
      }
    }
    if(found)
        result.push_back(w);
 }
 return result;
}
// To execute C++, please define "int main()"
int main() {
  //vector<string> words = { "hello, ", "world!", "\n" };
  //vector<string> words = { "hello", "world"};
  /*for (const string& word : words) {
    cout << word;
  }*/
vector<string> words={"cat","baby","dog","bird","car","ax"};
string str1="tcabnihjs"; //-> cat 
string str2="brhbahyraz" ;//-> baby 
string str3="test"; //-> Null/None 
vector<string> testcases;
testcases.push_back(str1);
testcases.push_back(str2);
testcases.push_back(str3);
for(auto testcase: testcases){
  std::cout<<"testcase:"<<testcase<<std::endl;
  auto rslt = find_embedded_word(words, testcase);
  std::cout<<"results:"<<std::endl;
  for (auto w: rslt) {
    cout << w<<std::endl;
  }
}

  return 0;
}

// Your Previous  code is preserved below:
// const _ = require('lodash');

// function helloWorld() {
//   console.log('Hello, World');
// }

// _.times(5, helloWorld);