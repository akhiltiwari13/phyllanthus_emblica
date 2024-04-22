#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "ConfigParser.h"
#include "DataReader.h"
#include "OutputWriter.h"
#include "TradingAlgo.h"

class Simulator {
public:
  static void runSimulation(const std::string &configFile,
                            const std::string &inputDataFile,
                            const std::string &outputFile);
};

#endif // SIMULATOR_H
