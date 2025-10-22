#include <iostream>
#include <VersionQueue.H>


// For checking VersionQueue Testability
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]){
    VersionQueue queue;

    // Enqueue some elements
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    queue.Enqueue(40);

    // Print the current version of the queue
    std::cout << "Current version: ";
    queue.Print(queue.GetCurrentVersion());

    // Dequeue an element
    int dequeued = queue.Dequeue();
    std::cout << "Dequeued element: " << dequeued << std::endl;

    // Print the current version after dequeue
    std::cout << "Current version after dequeue: ";
    queue.Print(queue.GetCurrentVersion());

    // Enqueue more elements
    queue.Enqueue(50);
    queue.Enqueue(60);

    // Print the current version after enqueue
    std::cout << "Current version after enqueue: ";
    queue.Print(queue.GetCurrentVersion());

    // Print the queue at historical versions
    std::cout << "Queue at version 1: ";
    queue.Print(1);

    std::cout << "Queue at version 3: ";
    queue.Print(3);

    std::cout << "Queue at version 5: ";
    queue.Print(5);

    return 0;
}

