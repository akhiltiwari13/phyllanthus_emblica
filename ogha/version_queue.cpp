#include <iostream>

class VersionQueue {
private:
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* front_;
    Node* back_;
    int current_version_;
public:
    VersionQueue() : front_(nullptr), back_(nullptr), current_version_(0) {}

    void Enqueue(int value) {
        Node* new_node = new Node(value);
        if (front_ == nullptr) {
            front_ = new_node;
        } else {
            back_->next = new_node;
        }
        back_ = new_node;
        current_version_++;
    }

    int Dequeue() {
        if (front_ == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        int value = front_->value;
        Node* old_front = front_;
        front_ = front_->next;
        delete old_front;
        current_version_++;
        return value;
    }

    void Print(int version) {
        if (version > current_version_) {
            throw std::out_of_range("Version does not exist");
        }
        Node* current = front_;
        while (current != nullptr && current->next != nullptr && current->next->value < version) {
            current = current->next;
        }
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};


int main(int argc, char* argv[]){
    return 0;
}
