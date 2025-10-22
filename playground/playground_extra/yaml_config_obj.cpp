#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

// Enum to specify storage type
enum class ConfigStorageType {
    HEAP,
    STACK
};

// Function to load YAML config and store it on the heap or stack
void loadAndPrintConfig(const std::string& filename, ConfigStorageType storageType) {
    try {
        // Load the YAML file
        YAML::Node config = YAML::LoadFile(filename);

        // Store the config on the heap or stack based on the storage type
        if (storageType == ConfigStorageType::HEAP) {
            // Store on the heap
            auto* heapConfig = new YAML::Node(config);
            std::cout << "Configuration loaded on the heap:" << std::endl;
            std::cout << *heapConfig << std::endl;
            delete heapConfig; // Clean up
        } else {
            // Store on the stack
            YAML::Node stackConfig = config;
            std::cout << "Configuration loaded on the stack:" << std::endl;
            std::cout << stackConfig << std::endl;
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "YAML Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <config_file.yaml> <storage_type>" << std::endl;
        std::cout << "  storage_type: 'heap' or 'stack'" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];
    std::string storageArg = argv[2];

    // Parse storage type
    ConfigStorageType storageType;
    if (storageArg == "heap") {
        storageType = ConfigStorageType::HEAP;
    } else if (storageArg == "stack") {
        storageType = ConfigStorageType::STACK;
    } else {
        std::cout << "Unknown storage type '" << storageArg << "'. Use 'heap' or 'stack'." << std::endl;
        return 1;
    }

    // Load and print the configuration
    loadAndPrintConfig(configFile, storageType);

    return 0;
}
