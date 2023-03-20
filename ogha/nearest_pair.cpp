/******************************************************************************
 * File:             nearest_pair.cpp
 *
 * Author:           akhil tiwari
 * Created:          03/12/23 
 * Description:      You are given a list of integers and must find the nearest pair that sum to a given target. For instance, given the list (1 5 3 6 4 2), if the target is 7, there                      are three pairs with the required sum, (1 6), (5 2) and (3 4), but pair (1 6) has two intervening numbers, pair (5 2) has three intervening numbers, and pair                          (3 4) has only one intervening number, so (3 4) is the nearest pair.
 *****************************************************************************/

#include <_types/_uint64_t.h>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

    /* template <typename T> */
/* void printElements (const T& coll) */
/* { */
    /* for (const auto& elem : coll) { */

    /*     std::cout << elem << "{ "<<elem.first<<", "<<elem.second<<"}"<<std::endl; */
    /* } */
/* } */

/* pair<uint64_t, uint64_t> nearest_pair_2_sum(vector<uint64_t>& vec, uint64_t b){ */
    /* pair<uint64_t,uint64_t> result{}; */
    /* /1* push elements of the array to an unordered_map <vec[idx],idx> *1/ */
    /* unordered_map<uint64_t, uint64_t> _map{}; */
    /* uint64_t idx{}; */
    /* for(auto ele: vec){ */
    /*     _map[ele]=idx++; */
    /* } */

    /* printElements(_map); */

    /* return result; */
/* } */   

/* int main(){ */
/*     /1* test code *1/ */
/*     vector<uint64_t> vec{1, 5, 3, 6, 4, 2}; */
/*     uint64_t sum{6}; */
/*     auto result = nearest_pair_2_sum(vec,sum); */
/*     std::cout<<"nearest_pair_2_sum: {"<<result.first<<", "<<result.second<<"}"<<std::endl; */

/*     return 0; */
/* } */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Helper function to compute the absolute difference between two integers
int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// Function to find the nearest pair that sum to a given target in a vector of integers
vector<int> nearest_pair(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end()); // sort the numbers in ascending order
    int left = 0, right = nums.size() - 1;
    int min_diff = INT_MAX; // initialize the minimum difference to the maximum integer value
    vector<int> result(2);
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            // found an exact match, return the pair
            result[0] = nums[left];
            result[1] = nums[right];
            return result;
        } else {
            // update the minimum difference and move the left or right pointer accordingly
            int diff = abs_diff(sum, target);
            if (diff < min_diff) {
                min_diff = diff;
                result[0] = nums[left];
                result[1] = nums[right];
            }
            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums {1, 5, 3, 6, 4, 2};
    int target = 7;
    vector<int> pair = nearest_pair(nums, target);
    cout << "Nearest pair to " << target << " is (" << pair[0] << ", " << pair[1] << ")" << endl;
    return 0;
}


