#include <VersionQueue.H>

void VersionQueue::Enqueue(int value) {
    Node* new_node = new Node(value, current_version_ + 1);
    if (front_ == nullptr) {
        front_ = new_node;
    } else {
       back_->next = new_node;
    }
    back_ = new_node;
    current_version_++;
}

int VersionQueue::Dequeue() {
    if (front_ == nullptr) {
        throw std::out_of_range("Queue is empty");
    }
    int value = front_->value;
    Node* old_front = front_;
    front_ = front_->next;
    current_version_++;
    if (front_ == nullptr) {
        back_ = nullptr;
    }
    //removed nodes are soft-deleted and added to a different linked list
    old_front->removed_next = removed_front_;
    removed_front_ = old_front;
    return value;
}

void VersionQueue::Print(int version) {
    if (version > current_version_) {
        throw std::out_of_range("Version does not exist");
    }
    Node* current = front_;
    Node* removed_current = removed_front_;
    while (current != nullptr || removed_current != nullptr) {
        // conditions to print the nodes in the order as per the specified version
        if (current != nullptr && (current->version <= version || removed_current == nullptr || current->version < removed_current->version)) {
            std::cout << current->value << " ";
            current = current->next;
        } else {
            std::cout << removed_current->value << " ";
            removed_current = removed_current->removed_next;
        }
    }
    std::cout << std::endl;
}

