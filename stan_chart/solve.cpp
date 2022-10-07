/* @todo: find a number n in a circularly sorted array. 8,9,10,1,2,3,4 => circular sorted */


#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solve(vector<int>&vec, int s, int e, int n){
    if(s>e)return -1;// n not found in the array
    int mid = (s+e)/2;
    if (vec[mid] == n) return mid;
    else{
        if(vec[mid]< n && vec[e]>n)
            return solve(vec,mid+1, e, n);
        else
            return solve(vec,s,mid-1,n);
    }
}

int main(int argc, char* argv[]){
    std::vector<int> v{8,9,10,1,2,3,4,5};
    std::cout<<solve(v,0,v.size()-1,8)<<std::endl;
    return 0;
}
