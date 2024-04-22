#include "Simulator.h"
#include <iostream>

void Simulator::runSimulation(const std::string& configFile, const std::string& inputDataFile, const std::string& outputFile) {
    // Parse configuration
    SimulationConfig config = ConfigParser::parseConfig(configFile);

    // Read input data
    // std::map<std::string, std::vector<double>> inputData = DataReader::readInputData(inputDataFile);
    auto inputData = DataReader::readInputData(inputDataFile);

    // Iterate over time points
    for (const auto& algoConfig : config.algoConfigs) {
        TradingAlgo algo(algoConfig);

        std::map<std::string, std::vector<double>> positions;

        for (const auto& it : inputData) {
            // std::vector<double> currentPositions = algo.run(it.first, it.second);
            // positions[it.first] = currentPositions;
            std::cout<<it<<std::endl;
        }

        // Write output data
        OutputWriter::writeOutputData(outputFile, positions);
    }
}
