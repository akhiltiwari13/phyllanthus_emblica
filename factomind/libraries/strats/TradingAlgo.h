#ifndef TRADING_ALGO_H
#define TRADING_ALGO_H

#include <string>
#include <map>
#include <vector>
#include "ConfigParser.h"

// struct AlgorithmConfig {
//     std::string algoName;
//     std::map<std::string, double> parameters;
// };
// fwd declaration
struct AlgorithmConfig; 

class TradingAlgo {
public:
    TradingAlgo(const AlgorithmConfig& config);
    std::vector<double> run(const std::string& time, const std::vector<double>& inputData);

private:
    AlgorithmConfig algoConfig;
};

#endif // TRADING_ALGO_H
