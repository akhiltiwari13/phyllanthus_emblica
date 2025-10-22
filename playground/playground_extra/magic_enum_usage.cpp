#include <magic_enum.hpp>
#include <iostream>

enum class Color { Red, Green, Blue };

enum class Flags {
    Read = 1 << 0,
    Write = 1 << 1,
    Execute = 1 << 2
};

// Customize string representation
template <>
struct magic_enum::customize::enum_name<Flags> {
    static constexpr std::string_view name(Flags value) {
        switch (value) {
            case Flags::Read: return "ReadPermission";
            case Flags::Write: return "WritePermission";
            case Flags::Execute: return "ExecutePermission";
            default: return {}; // Let the default behavior handle other values
        }
    }
};

enum class Numbers { One = 1, Two, Three, Four, Five };

// Specify a range of values
constexpr auto numbers = magic_enum::enum_values<Numbers, 
                                                 Numbers::Two, 
                                                 Numbers::Four>();
// numbers contains: Two, Three, Four

int main() {
    // Enum to string
    Color color = Color::Red;
    std::cout << magic_enum::enum_name(color) << std::endl; // "Red"
    
    // String to enum
    auto blue = magic_enum::enum_cast<Color>("Blue");
    if (blue.has_value()) {
        std::cout << "Converted string to enum: " 
                  << static_cast<int>(blue.value()) << std::endl; // 2
    }
    
    // Iteration
    std::cout << "Colors:" << std::endl;
    for (const auto& c : magic_enum::enum_values<Color>()) {
        std::cout << "- " << magic_enum::enum_name(c) << std::endl;
    }
    
    // Count
    std::cout << "Number of colors: " 
              << magic_enum::enum_count<Color>() << std::endl; // 3
    
    return 0;
}
