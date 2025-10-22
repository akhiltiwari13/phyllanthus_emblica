#include "TradingStrategy.h"
#include <iostream>

PositionMatrix Strat1::run(const std::map<std::string, double>& params) {
    // Implement the algorithm logic here
    std::cout << "Running Strat1 with params:" << std::endl;
    for (const auto& param : params) {
        std::cout << param.first << ": " << param.second << std::endl;
    }
    std::cout << std::endl;

    // Sample positions
    PositionMatrix positions = {{1.0, 2.0, 3.0}, {-1.0, -2.0, -3.0}};

    return positions;
}

PositionMatrix Strat2::run(const std::map<std::string, double>& params) {
    // Implement the algorithm logic here
    std::cout << "Running Strat2 with params:" << std::endl;
    for (const auto& param : params) {
        std::cout << param.first << ": " << param.second << std::endl;
    }
    std::cout << std::endl;

    // Sample positions
    PositionMatrix positions = {{0.5, 1.0, 1.5}, {-0.5, -1.0, -1.5}};

    return positions;
}

StratBase* createAlgorithm() {
    // Determine the algorithm based on some criteria
    // For simplicity, always return Algo1 in this example
    return new Strat2();
}

