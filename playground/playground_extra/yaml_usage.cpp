#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#include <string>

struct Vec3 {
    float x, y, z;
};

// Convert Vec3 to/from YAML
namespace YAML {
    template<>
    struct convert<Vec3> {
        static Node encode(const Vec3& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node& node, Vec3& rhs) {
            if(!node.IsSequence() || node.size() != 3) {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
}


int main() {
    // Parse from string
    YAML::Node config = YAML::Load("[1, 2, 3, 4, 5]");
    
    // Parse from file
    YAML::Node config2 = YAML::LoadFile("config.yaml");
    
    // Accessing values
    if (config2["name"]) {
        std::cout << "Name: " << config2["name"].as<std::string>() << std::endl;
    }
    
    // Iterating through a sequence
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
        std::cout << "Value: " << it->as<int>() << std::endl;
    }
    
    // Iterating through a map
    if (config2["mapping"]) {
        for (const auto& it : config2["mapping"]) {
            std::cout << it.first.as<std::string>() << ": " << it.second.as<std::string>() << std::endl;
        }
    }
    
    // Checking if a node exists
    if (config2["database"] && config2["database"]["host"]) {
        std::cout << "Host: " << config2["database"]["host"].as<std::string>() << std::endl;
    }
    
    // Create a YAML node
    YAML::Node node;
    
    // Build a sequence
    node["sequence"].push_back("item1");
    node["sequence"].push_back("item2");
    node["sequence"].push_back("item3");
    
    // Build a map
    node["mapping"]["key1"] = "value1";
    node["mapping"]["key2"] = "value2";
    
    // Nested structures
    node["database"]["host"] = "localhost";
    node["database"]["port"] = 3306;
    node["database"]["credentials"]["username"] = "user";
    node["database"]["credentials"]["password"] = "pass";
    
    // Output to string
    std::string output = YAML::Dump(node);
    std::cout << output << std::endl;
    
    // Output to file
    std::ofstream file("output.yaml");
    file << YAML::Dump(node);
    
    // Create a Vec3
    Vec3 position = {1.0f, 2.0f, 3.0f};
    
    // Emit it
    YAML::Node node;
    node["position"] = position;
    std::cout << YAML::Dump(node) << std::endl;
    
    // Parse it
    Vec3 newPosition = node["position"].as<Vec3>();
    std::cout << "Position: " << newPosition.x << ", " 
              << newPosition.y << ", " << newPosition.z << std::endl;
    
    return 0;
}
