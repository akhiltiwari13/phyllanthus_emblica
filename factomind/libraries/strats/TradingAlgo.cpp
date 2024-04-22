#include "TradingAlgo.h"
#include "ConfigParser.h"

TradingAlgo::TradingAlgo(const AlgorithmConfig &config) : algoConfig(config) {}

std::vector<double> TradingAlgo::run(const std::string &time,
                                     const std::vector<double> &inputData) {
  std::vector<double> positions;

  // TODO: Algorithm logic implementation
  // ...

  return positions;
}
