#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <map>
#include <string>
#include <vector>

namespace sim::cfg {
struct AlgorithmConfig {
  std::string algoName;
  std::map<std::string, std::string> parameters;
};

struct SimulationConfig {
  std::string inputFile;
  std::string outputFile;
  std::string logFile;
  std::string startTime;
  std::string endTime;
  std::vector<AlgorithmConfig> algoConfigs;
};

class ConfigParser {
private:
  SimulationConfig simCfg;

public:
  static SimulationConfig parseConfig(const std::string &configFile,
                                      SimulationConfig &config);
  void logConfig() const;
  SimulationConfig &getConfig();
};

} // namespace sim::cfg

#endif // CONFIG_PARSER_H
