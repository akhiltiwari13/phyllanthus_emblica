#ifndef DATA_READER_H
#define DATA_READER_H

#include <string>
#include <unordered_map>
#include <vector>

#include <common/TimeSeriesData.h>

namespace sim::dreader {

class DataReader {
private:
  static sim::common::TimeSeriesData priceData;

public:
  static void readInputData(const std::string &inputFile);
  void printPriceData() const;
  sim::common::TimeSeriesData getPriceData() const;
};

} // namespace sim::dreader

#endif // DATA_READER_H