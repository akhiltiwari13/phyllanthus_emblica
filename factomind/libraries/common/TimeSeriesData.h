#ifndef TIME_SERIES_DATA_H
#define TIME_SERIES_DATA_H
#include <map>
#include <string>
#include <vector>

namespace sim::common {
    // TimeSeries data: Represented using a map of timestamps per symbol
    // timestamp(key) | Value of <symbol | price> (value)
    // boost::multi_index_container is also a viable option to represent the
    // time-series data typedef std::unordered_map<std::string,
    // std::vector<std::pair<SYMBOL, double>>> PriceDataCache;
    // typedef std::unordered_map<std::string, std::unordered_map<SYMBOL, double>>
    //     TimeSeriesData;

    // struct TimeSeriesData {
    //   std::set<std::string> timestamps;
    //   std::unordered_map<std::string, std::vector<double>> data; //timestamps |
    //   <price1, price2, price3.....> for each array
    // };
    struct TimeSeriesData {
        std::vector<std::string> symbols{};
        std::map<std::string, std::vector<double>>
            data{}; // ordered-map so the order of value in the vector would be same
                    // as the timestamp values.
        TimeSeriesData() noexcept;
        TimeSeriesData(const std::vector<std::string> &symbolList) noexcept; 
    };

} // namespace sim::common
#endif
