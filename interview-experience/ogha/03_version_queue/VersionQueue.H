#pragma once
#include <iostream>
#include <stdexcept>

class VersionQueue {
    private:
        struct Node {
            int value;
            int version;
            Node* next;
            Node* removed_next;
            Node(int val, int ver) : value(val), version(ver), next(nullptr), removed_next(nullptr) {}
        };

        Node* front_;
        Node* back_;
        int current_version_;
        Node* removed_front_;
    public:
        VersionQueue() : front_(nullptr), back_(nullptr), current_version_(0), removed_front_(nullptr) {}

        void Enqueue(int value); 

        int Dequeue();

        void Print(int version);

        inline int GetCurrentVersion() const {
            return current_version_;
        }
};

