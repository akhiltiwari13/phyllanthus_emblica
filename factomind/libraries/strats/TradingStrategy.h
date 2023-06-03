#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

#include <map>
#include <vector>

using DataMatrix = std::vector<std::vector<double>>;
using PositionMatrix = std::vector<std::vector<double>>;

class StratBase {
    public:
        virtual ~StratBase() {}
        virtual PositionMatrix run(const std::map<std::string, double>& params) = 0;
};

// Trading Strategy 1
class Strat1 : public StratBase {
    public:
        PositionMatrix run(const std::map<std::string, double>& params) override;
};

// Trading Strategy 2
class Strat2 : public StratBase {
    public:
        PositionMatrix run(const std::map<std::string, double>& params) override;
};

// Function to create an instance of the trading Strategy based on the algoName
extern "C" StratBase* createAlgorithm();

#endif  // TRADING_STRATEGY_H

