#include <folly/FBString.h>
#include <iostream>
#include <folly/dynamic.h>
#include <folly/futures/Future.h>
#include <thread>

int main() {
    folly::fbstring str = "Hello, Folly!";
    str.append(" This is a high-performance string.");
    
    std::cout << str << std::endl;
    std::cout << "Length: " << str.length() << std::endl;
    
    // Can be used as a drop-in replacement for std::string
    str.replace(7, 5, "Facebook");
    
    // Create a promise
    folly::Promise<int> promise;
    
    // Get the future from the promise
    folly::Future<int> future = promise.getFuture();
    
    // Set value in a different thread
    std::thread t([p = std::move(promise)]() mutable {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p.setValue(42);
    });
    
    // Wait for the value and use it
    future.then([](folly::Try<int> result) {
        std::cout << "The answer is: " << result.value() << std::endl;
    });
    
    t.join();
    
    // Chain futures
    folly::makeFuture<int>(123)
        .then([](int value) {
            return value * 2;
        })
        .then([](int value) {
            std::cout << "Final value: " << value << std::endl;
            return folly::unit;
        });
    
    // Create dynamic objects
    folly::dynamic obj = folly::dynamic::object;
    obj["integer"] = 123;
    obj["string"] = "hello world";
    obj["array"] = folly::dynamic::array(1, 2, 3);
    obj["nested"] = folly::dynamic::object("key", "value");
    
    // Access values
    std::cout << "Integer: " << obj["integer"].asInt() << std::endl;
    std::cout << "String: " << obj["string"].asString() << std::endl;
    
    // Iterate through an array
    for (auto& val : obj["array"]) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Convert to JSON
    std::cout << "JSON: " << folly::toJson(obj) << std::endl;
    
    return 0;
}
