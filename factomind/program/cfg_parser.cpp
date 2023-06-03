#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

int main()
{
    YAML::Node config = YAML::LoadFile("../cfg/config.yaml");

    std::cout << "Simulation Info:\n";
    std::cout << "StartTime: " << config["Simulation"]["Info"]["StartTime"].as<std::string>() << "\n";
    std::cout << "EndTime: " << config["Simulation"]["Info"]["EndTime"].as<std::string>() << "\n";
    std::cout << "Algo:\n";

    for (const auto& sample : config["Simulation"]["Algo"])
    {
        std::cout << sample.first.as<std::string>() << ":\n";
        std::cout << "Algoname: " << sample.second["Algoname"].as<std::string>() << "\n";
        std::cout << "param1: " << sample.second["param1"].as<double>() << "\n";
        std::cout << "param2: " << sample.second["param2"].as<int>() << "\n";

        if (sample.first.as<std::string>() == "SimSample3")
        {
            std::cout << "var1: " << sample.second["var1"].as<int>() << "\n";
            std::cout << "var2: " << sample.second["var2"].as<int>() << "\n";
            std::cout << "var3: " << sample.second["var3"].as<double>() << "\n";
        }
    }

    return 0;
}

