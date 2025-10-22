#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/chrono.h>
#include <vector>
#include <chrono>

int main() {
    // Basic usage
    fmt::print("Hello, {}!\n", "world");
    
    // Named arguments
    fmt::print("Hello, {name}! The answer is {number}.\n", 
               fmt::arg("name", "World"), fmt::arg("number", 42));
    
    // Format to string
    std::string s = fmt::format("The answer is {}.", 42);
    
    // Multiple arguments
    fmt::print("The numbers are {}, {}, and {}.\n", 1, 2, 3);
    
    // Format specifiers
    fmt::print("Hexadecimal: {:x}\n", 42);       // 2a
    fmt::print("Scientific: {:e}\n", 1.23e-4);   // 1.230000e-04
    fmt::print("Fixed: {:.2f}\n", 1.234);        // 1.23
    fmt::print("Binary: {:b}\n", 42);            // 101010
    
    // Container formatting
    std::vector<int> v = {1, 2, 3};
    fmt::print("Vector: {}\n", v);               // [1, 2, 3]
    
    // Date and time formatting
    auto now = std::chrono::system_clock::now();
    fmt::print("Current time: {:%Y-%m-%d %H:%M:%S}\n", now);
    
    // Alignment and width
    fmt::print("|{:10}|{:10}|\n", "left", "right");   // |left      |     right|
    fmt::print("|{:<10}|{:>10}|\n", "left", "right"); // |left      |     right|
    fmt::print("|{:^10}|{:^10}|\n", "mid", "center"); // |   mid    |  center  |
    
    return 0;
}
