/* #include <bits/stdc++.h> */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

/* argument map has {child,parent} pair */
int largestTree(const std::unordered_map<int,int>& immediateParent)
{
/* to return the id of the root of largest tree!! */
    std::unordered_set<int> roots;
    for(auto& itr: immediateParent){
        roots.insert(itr.second);
    }

    for(auto& itr: immediateParent){
        if(roots.find(itr.first) != roots.end()){
            roots.erase(itr.first);
        }
    }
    
    //roots has all the roots for all trees.
    //
    return 0;
}

bool doTestsPass(){
    std::vector<std::pair<std::unordered_map<int,int>,int>> testCases={
        /* sample test cases. */
    };
    bool passed = true;
    for(unsigned int ii =0 ; ii< testCases.size(); ++ii){
        int actual = largestTree(testCases[ii].first);
        if(actual != testCases[ii].second){
            passed = false;
            std::cout << "Failed for case" << ii << ", expected "<< testCases[ii].second<< ", actual "<< actual <<std::endl;
        }
    }
    return passed;
}

int main() {

    /* run the tests. */
    if(doTestsPass()){
        std::cout<< "ALL TESTS PASS." << std::endl;
    }
    else{
        std::cout<< "TESTS FAILED."<<std::endl;
    }
    return 0;
}
