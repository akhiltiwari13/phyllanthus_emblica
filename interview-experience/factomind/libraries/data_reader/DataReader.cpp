#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <data_reader/DataReader.h>

namespace sim::dreader {

// common::TimeSeriesData DataReader::priceData{};
// std::vector<std::string> DataReader::symbolList{};

void DataReader::readInputData(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }

  std::string line;
  std::vector<std::string> symbolList;
  std::getline(file, line); // Parse the header line and save the symbol names;
  boost::split(symbolList, line, boost::is_any_of(","));
  DataReader::priceData(symbolList); //initialize priceData with the list of symbols


  while (std::getline(file, line)) {
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(","));

    if (tokens.size() > 1) {
      std::string timestamp = tokens[0];
      DataReader::priceData.timestamps.push_back(timestamp);
      for (size_t i = 1; i < tokens.size(); ++i) {
        std::cout << "token[i]: " << tokens[i];
        BOOST_LOG_TRIVIAL(debug) << "tokens["<<i<<"]: "<< tokens[i];
        try {
          double price = std::stod(tokens[i]);

          if (DataReader::priceData.find(timestamp) ==
              DataReader::priceData.end()) {
            DataReader::priceData.[timestamp] =
                std::vector<std::pair<SYMBOL, double>>();
          }

          DataReader::priceData[timestamp].push_back(
              {static_cast<SYMBOL>(i), price});

        } catch (std::invalid_argument &e) {
          std::cerr << "Error: " << e.what() << "for token: " << tokens[i]
                    << " & symbol " << to_string(static_cast<SYMBOL>(i))
                    << std::endl;
        }
      }
    }
  }

  file.close();
}

void DataReader::printPriceData() const {
  for (const auto &pair : priceData) {
    const std::string &timestamp = pair.first;
    std::cout << timestamp << ": ";
    const std::vector<std::pair<SYMBOL, double>> &symbolPrices = pair.second;

    for (auto symPrice : symbolPrices) {
      std::cout << to_string(symPrice.first) << ":" << symPrice.second << "|";
    }
    std::cout << std::endl;
  }
}

common::TimeSeriesData DataReader::getPriceData() const { return priceData; }
} // namespace sim::dreader