#include "OutputWriter.h"
#include "Utils.h"
#include <fstream>
#include <sys/_types/_size_t.h>

namespace sim::dwirter {
void OutputWriter::writeOutputData(
    const std::string &outputFile,
    const utils::PriceDataCache& positions){
    // const std::map<std::string, std::vector<double>> &positions) {
  std::ofstream file(outputFile);
  if (file.is_open()) {
    // Write header
    file << "Timestamp";
    for (size_t i=0 ; i<static_cast<size_t>(utils::SYMBOL::INVALID); ++i) {
      file << "," << utils::to_string(static_cast<utils::SYMBOL>(i));
    }
    file << std::endl;

    // Write position data
    for (auto itr: positions) {
      file << itr.first<<", ";
      for (size_t i = 0; i < positions.begin()->second.size(); ++i) {
      file << positions.begin()->second[i];
      for (const auto &it : positions) {
        file << "," << it.second[i];
      }
      file << std::endl;
    }
    }

    file.close();
  }
}
} // namespace sim::dwirter