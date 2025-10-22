#include <ConfigParser.h>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


namespace sim::cfg {
SimulationConfig ConfigParser::parseConfig(const std::string &configFile,
                                           SimulationConfig &config) {
  // Parse the YAML configuration file
  YAML::Node root = YAML::LoadFile(configFile);

  // Parse simulation info
  YAML::Node infoNode = root["Simulation"]["Info"];
  config.inputFile = infoNode["InputFilePath"].as<std::string>();
  config.outputFile = infoNode["OutputFilePath"].as<std::string>();
  config.logFile = infoNode["LogFilePath"].as<std::string>();
  config.startTime = infoNode["StartTime"].as<std::string>();
  config.endTime = infoNode["EndTime"].as<std::string>();

  // Parse algorithm configs
  YAML::Node algoNode = root["Simulation"]["Algo"];
  for (const auto &it : algoNode) {
    AlgorithmConfig algoConfig;
    algoConfig.algoName = it.second["Algoname"].as<std::string>();

    // Parse algorithm parameters
    YAML::Node paramNode = it.second;
    for (const auto &param : paramNode) {
      if (param.first.as<std::string>() != "Algoname") {
        algoConfig.parameters[param.first.as<std::string>()] =
            param.second.as<std::string>();
      }
    }

    config.algoConfigs.push_back(algoConfig);
  }

  return config;
}

void ConfigParser::logConfig() const {
  // Log to stdout & logfile
  std::cout << "Simulation:" << std::endl;
  std::cout << "\tInfo:" << std::endl;
  std::cout << "\t\tInputFilePath: " << simCfg.inputFile << std::endl;
  std::cout << "\t\tOutputFilePath: " << simCfg.outputFile << std::endl;
  std::cout << "\t\tLogFilePath: " << simCfg.logFile << std::endl;
  std::cout << "\t\tStartTime: " << simCfg.startTime << std::endl;
  std::cout << "\t\tEndTime: " << simCfg.endTime << std::endl;
  std::cout << "\tAlgo:" << std::endl;
  BOOST_LOG_TRIVIAL(info) << "Simulation:";
  BOOST_LOG_TRIVIAL(info) << "\tInfo:";
  BOOST_LOG_TRIVIAL(info) << "\t\tInputFile: " << simCfg.inputFile;
  BOOST_LOG_TRIVIAL(info) << "\t\tOutputFile: " << simCfg.outputFile;
  BOOST_LOG_TRIVIAL(info) << "\t\tLogFile: " << simCfg.logFile;
  BOOST_LOG_TRIVIAL(info) << "\t\tStartTime: " << simCfg.startTime;
  BOOST_LOG_TRIVIAL(info) << "\t\tEndTime: " << simCfg.endTime;
  BOOST_LOG_TRIVIAL(info) << "\tAlgo: " << simCfg.endTime;

  for (auto algoCfg : simCfg.algoConfigs) {
    std::cout << "\t\t\tAlgoName: " << algoCfg.algoName << std::endl;
    BOOST_LOG_TRIVIAL(info) << "\t\t\tAlgoName: " << algoCfg.algoName;
    for (auto algoParam : algoCfg.parameters) {
      std::cout << "\t\t\t" << algoParam.first << ": " << algoParam.second
                << std::endl;
      BOOST_LOG_TRIVIAL(info) << "\t\t\t" << algoParam.first << ": "
                              << algoParam.second << std::endl;
    }
  }
}

SimulationConfig& ConfigParser::getConfig() { return simCfg; }
}