#include "ConfigParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <yaml-cpp/yaml.h>

std::map<std::string, std::map<std::string, double>> parseConfig(const std::string& filename) {
    std::map<std::string, std::map<std::string, double>> algoConfigs;

    // Read the YAML file
    YAML::Node config = YAML::LoadFile(filename);

    // Iterate over the algorithm configurations
    for (const auto& simConfig : config["Simulation"]["Algo"]) {
        std::string algoName = simConfig.first.as<std::string>();
        std::map<std::string, double> params;

        // Iterate over the parameters
        for (const auto& param : simConfig.second) {
            std::string paramName = param.first.as<std::string>();
            double paramValue = param.second.as<double>();
            params[paramName] = paramValue;
        }

        algoConfigs[algoName] = params;
    }

    std::cout<<"config parsing completed"<<std::endl;
    return algoConfigs;
}
