#include <common/TimeSeriesData.h>

namespace sim::common {

    TimeSeriesData::TimeSeriesData() noexcept {}

    TimeSeriesData::TimeSeriesData(const std::vector<std::string> &symbolList) :symbols(symbolList) noexcept{
        /* for (auto &symbol : symbolList) { */
        /*     data.insert({symbol, {}}); // insert the symbol into the map along with an */
        /* } */
    }

} // namespace sim::common
