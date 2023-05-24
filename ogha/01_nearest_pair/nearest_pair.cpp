/***************************************************************************************************************
 * File:             nearest_pair.cpp
 *
 * Author:           akhil tiwari
 * Created:          05/21/23 
 * Description:      You are given a list of integers and must find the nearest pair that sum to a given target. For instance, given the list (1 5 3 6 4 2), if the 
 *                   target is 7, there are three pairs with the required sum, (1 6), (5 2) and (3 4), but pair (1 6) has two intervening numbers, pair (5 2) has 
 *                   three intervening numbers, and pair (3 4) has only one intervening number, so (3 4) is the nearest pair.
 ***************************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Function to find the nearest pair that sum to a given target in a vector of integers
// for more that one such pairs the function returns just one of such pairs
std::pair<int,int> nearest_pair(vector<int>& nums, int target) {

    unordered_map<int,unordered_set<size_t>> _cache{};
    size_t left = 0, right = nums.size() - 1;
    int min_diff = std::numeric_limits<int>::max(); // initialize the minimum difference to the maximum integer value
    std::pair<int,int> result{-1,-1};

    //populate the cache
    size_t idx{};
    for(auto ele: nums){
        _cache[ele] = unordered_set<size_t>{};
        _cache[ele].insert(idx++);
    }

    sort(nums.begin(), nums.end()); // sort the numbers in ascending order

    while (left < right) {
        int sum = nums[left] + nums[right];//check the sum and update the left and right indices
        if (sum == target) {
            // calculate min_diff for all occurances of the pair in the original vector
            for(auto lidx: _cache[nums[left]]){
                for(auto ridx: _cache[nums[right]]){
                    auto diff = min(min_diff, abs(static_cast<int>(lidx)-static_cast<int>(ridx)));
                    if(diff < min_diff){
                        result.first  = nums[left];
                        result.second = nums[right];
                        min_diff = diff;
                    }
                }
            }
        left++;
        }else{
        sum < target?++left:--right;
        } 
    }
    return result;
}

int main() {
    vector<int> nums {1, 5, 3, 3, 13, -1, 6, 6, 8, 4, 4, 4, 2};
    int target = 12;
    auto result = nearest_pair(nums, target);
    cout << "Nearest pair to " << target << " is (" << result.first << ", " << result.second << ")" << endl;
    return 0;
}


