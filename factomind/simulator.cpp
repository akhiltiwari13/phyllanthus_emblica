#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <csv-parser/csv.hpp>
#include <yaml-cpp/yaml.h>

// Define the data structures for input and output
using DataMatrix = std::vector<std::vector<double>>;
using PositionMatrix = std::vector<std::vector<double>>;

// Function to read input data from a CSV file
DataMatrix readInputData(const std::string& filename) {
  DataMatrix data;

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open input data file: " << filename << std::endl;
    return data;
  }

  // Use CSV-parser library to parse the CSV file
  csv::CSVFormat format;
  format.delimiter(',');

  csv::CSVReader reader(file, format);
  for (csv::CSVRow& row : reader) {
    std::vector<double> rowData;
    for (csv::CSVField& field : row) {
      rowData.push_back(field.get<double>());
    }
    data.push_back(rowData);
  }

  return data;
}

// Base class for trading algorithms
class TradingAlgorithm {
public:
  virtual PositionMatrix run(const DataMatrix& inputData, const std::map<std::string, double>& params) = 0;
};

// Example implementation of a trading algorithm
class Algo1 : public TradingAlgorithm {
public:
  PositionMatrix run(const DataMatrix& inputData, const std::map<std::string, double>& params) override {
    PositionMatrix positions(inputData.size(), std::vector<double>(inputData[0].size(), 0.0));

    for (size_t ti = 1; ti < inputData.size(); ++ti) {
      for (size_t ii = 0; ii < inputData[ti].size(); ++ii) {
        positions[ti][ii] = inputData[ti - 1][ii] - inputData[ti - 2][ii];
      }
    }

    return positions;
  }
};

// Function to parse the configuration file and return algorithm configurations
std::map<std::string, std::map<std::string, double>> parseConfig(const std::string& filename) {
  std::map<std::string, std::map<std::string, double>> algoConfigs;

  try {
    YAML::Node config = YAML::LoadFile(filename);
    const YAML::Node& algoConfigNode = config["Simulation"]["Algo"];

    for (const auto& algoNode : algoConfigNode) {
      std::string algoName = algoNode.first.as<std::string>();
      std::map<std::string, double> params;

      for (const auto& paramNode : algoNode.second) {
        std::string paramName = paramNode.first.as<std::string>();
        double paramValue = paramNode.second.as<double>();
        params[paramName] = paramValue;
      }

      algoConfigs[algoName] = params;
    }
  } catch (const YAML::Exception& e) {
    std::cerr << "Failed to parse config file: " << e.what() << std::endl;
  }

  return algoConfigs;
}

// Function to write output data to a CSV file
void writeOutputData(const std::string& filename, const PositionMatrix& positions) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open output data file: " << filename << std::endl;
    return;
  }

  for (const auto& row : positions) {
    for (size_t i = 0; i < row.size(); ++i) {
      file << row[i];
      if (i < row.size() - 1) {
        file << ",";
      }
    }
    file << std::endl;
  }

  file.close();
}

int main() {
  std::string configFilename = "config.yaml";
  std::string inputFilename = "input.csv";
  std::string outputFilename = "output.csv";

  // Read input data
  DataMatrix inputData = readInputData(inputFilename);
  if (inputData.empty()) {
    return 1;
  }

  // Parse configuration file
  std::map<std::string, std::map<std::string, double>> algoConfigs = parseConfig(configFilename);

  // Iterate over algorithm configurations and run simulations
  for (const auto& algoConfig : algoConfigs) {
    std::string algoName = algoConfig.first;
    const std::map<std::string, double>& params = algoConfig.second;

    // Create an instance of the trading algorithm based on the algoName
    TradingAlgorithm* algorithm = nullptr;
    if (algoName == "Algo1") {
      algorithm = new Algo1();
    } else {
      std::cerr << "Invalid algorithm name: " << algoName << std::endl;
      continue;
    }

    // Run the algorithm and get the positions
    PositionMatrix positions = algorithm->run(inputData, params);

    // Write output data to a CSV file
    writeOutputData(outputFilename, positions);

    delete algorithm;
  }

  return 0;
}
