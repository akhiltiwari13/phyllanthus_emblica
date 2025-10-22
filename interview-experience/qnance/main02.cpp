/**
 * author: akhil
 * program iterates through all the input string as and checks if it is malicious
 * Time Complexity O(n^2) where n is the length of the array of doubles.
 **/

#include <iostream>
#include <vector>

using namespace std;

// parse the array and count each element lying between the upper & lower bounds.
vector<int> count_elements(vector<double> A) {
    int n = A.size();
    vector<int> B(n, 0);
    for (int i = 0; i < n; i++) {
        double lower_bound = A[i];
        double upper_bound = A[i] + 1;
        for (int j = 0; j < n; j++) {
            if (A[j] >= lower_bound && A[j] < upper_bound) {
                B[i]++;
            }
        }
    }
    return B;
}


//test code
int main(int argc, char * argv[]){
    std::vector<double> A{1, 1.5, 2, 2.2, 2.5, 4, 4.6, 4.9, 4.99};

    std::cout<<"***********Array A: "<<std::endl;
    for(auto ele: A){
        std::cout<<ele<<" ";
    }
    cout<<endl;

    cout<<"count_elements()"<<endl;
    auto result = count_elements(A);

    std::cout<<"***********Array B: "<<std::endl;
    for(auto ele: result){
        std::cout<<ele<<" ";
    }
    cout<<endl;

    return 0;
}
