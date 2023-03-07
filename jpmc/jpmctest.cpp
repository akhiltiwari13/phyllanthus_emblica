/**
 * @file jpmctest.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief jpmc quant-researcher interview round 1
 * @version 0.1
 * @date 2023-03-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
using namespace std;

template<typename T>
class Vec{
    private:
        T* ptr;
        std::size_t capacity;
        
    public:
        Vec(std::size_t c):capacity(c){
            ptr = new T[c];
        };

        Vec(const Vec& obj){
            ptr = obj.ptr;
            capacity = obj.capacity;
            ptr = new T[capacity];
        }

        Vec& operator=(const Vec& rhs){
            this->ptr = rhs.ptr;
            return *this;
        }

        Vec(const Vec&& obj){
            ptr = std::move(obj.ptr);
        }

        Vec& operator=(const Vec&& rhs){
            this->ptr = std::move(rhs.ptr);
            return *this;
        }

        ~Vec(){
            delete[] ptr;
        };

        const T& operator[](const std::size_t idx){
          return ptr[idx];
        }

};

int main(){
    Vec<int> v(5);
    for(int i=0; i<5; ++i){
        std::cout<<v[i];
    }

    Vec<int> tv(v);
    Vec<int> tv2 = std::move(v);
}