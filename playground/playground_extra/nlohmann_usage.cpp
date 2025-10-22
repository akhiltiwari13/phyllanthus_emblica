#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // Create a JSON object
    json j = {
        {"name", "John Doe"},
        {"age", 30},
        {"is_active", true},
        {"interests", {"coding", "reading", "hiking"}}
    };

    // Serialize to string
    std::string s = j.dump(4);  // The 4 specifies the indentation
    std::cout << s << std::endl;

    // Parse from string
    json parsed = json::parse(R"({"happy": true, "pi": 3.141})");
    
    // Access elements
    std::string name = j["name"];
    int age = j["age"];
    bool active = j["is_active"];
    
    // Modify elements
    j["age"] = 31;
    j["address"] = {
        {"street", "123 Main St"},
        {"city", "Anytown"},
        {"country", "USA"}
    };
    json array = json::array();
    array.push_back(1);
    array.push_back("string");
    array.push_back(3.14);
    
    // Iterate through array
    for (const auto& element : array) {
        std::cout << element << std::endl;
    }
    
    // Access array elements
    int first = array[0];
    std::string second = array[1];

    std::cout << age << active << std::endl;

    json temp = {
        {"integer", 42},
        {"floating", 3.14},
        {"string", "hello world"},
        {"boolean", true},
        {"array", {1, 2, 3}},
        {"object", {{"key", "value"}}}
    };

    // Check types
    bool is_int = temp["integer"].is_number_integer();  // true
    bool is_float = temp["floating"].is_number_float(); // true
    bool is_string = temp["string"].is_string();        // true
    bool is_boolean = temp["boolean"].is_boolean();     // true
    bool is_array = temp["array"].is_array();           // true
    bool is_object = temp["object"].is_object();  

    std::cout << first << is_int << is_float << is_string << is_boolean << is_array << is_object << std::endl;
    
    return 0;
}
