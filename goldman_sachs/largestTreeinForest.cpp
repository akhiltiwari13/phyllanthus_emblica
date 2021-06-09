#include <bits/stdc++.h>
using namespace std;

/* argument map has {child,parent} pair */
int largestTree(const unordered_map<int,int>& immediateParent)
{
//to return the id of the root of largest tree!!
    unordered_set<int> roots;
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
void problemDemo(){

}

int main() {

    problemDemo();
    return 0;
}
