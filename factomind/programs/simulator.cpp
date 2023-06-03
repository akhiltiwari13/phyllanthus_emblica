#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <csv_parser/csv.hpp>
#include "ConfigParser.h"
#include <yaml-cpp/yaml.h>
#include <strats/TradingStrategy.h>

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

int main(int argc, char* argv[]) {
    std::string configFilename = "./config.yaml";
    std::string inputFilename = "./Close.csv";
    std::string outputFilename = "./output.csv";

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
        StratBase* algorithm = nullptr;
        if (algoName == "Strat1") {
            algorithm = new Strat1();
        } else {
            std::cerr << "Invalid algorithm name: " << algoName << std::endl;
            continue;
        }

        // Run the algorithm and get the positions
        /* PositionMatrix positions = algorithm->run(inputData, params); */
        PositionMatrix positions = algorithm->run(params);

        // Write output data to a CSV file
        writeOutputData(outputFilename, positions);

        delete algorithm;
    }

    return 0;
}
