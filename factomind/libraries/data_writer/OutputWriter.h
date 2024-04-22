#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include <map>
#include <string>
#include <vector>
#include <Utils.h>

namespace sim::dwirter {

class OutputWriter {
public:
  static void
  //   writeOutputData(const std::string &outputFile,
  //                   const std::map<std::string, std::vector<double>>
  //                   &positions);
  writeOutputData(const std::string &outputFile,
                  const sim::common::PriceDataCache &positions);
};

} // namespace sim::dwirter
#endif // OUTPUT_WRITER_H
