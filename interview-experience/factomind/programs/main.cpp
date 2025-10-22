// #include "Simulator.h"
#include <config_parser/ConfigParser.h>
#include "DataReader.h"
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
using namespace sim::cfg;

void initialize_logging(const std::string logFile) {
  auto sink = logging::add_file_log(logFile);
  sink->set_formatter(
      expr::stream
      << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
                                                          "%Y-%m-%d %H:%M:%S")
      << " [" << expr::attr<logging::trivial::severity_level>("Severity") << "]"
      << " ["
      << expr::attr<logging::attributes::current_thread_id::value_type>(
             "ThreadID")
      << "]"
      << " ["
      << expr::attr<logging::attributes::current_process_id::value_type>(
             "ProcessID")
      << "]"
      << " " << expr::smessage);
  logging::add_common_attributes();
}

int main() {
  std::string configFile = "config.yaml";

  sim::cfg::ConfigParser cfgParser{};
  sim::cfg::ConfigParser::parseConfig(configFile, cfgParser.getConfig());
  initialize_logging(cfgParser.getConfig().logFile);

  cfgParser.logConfig();
  BOOST_LOG_TRIVIAL(info) << "Dummy Log";

  sim::dreader::DataReader::readInputData(cfgParser.getConfig().inputFile);
  sim::dreader::DataReader dr{};
  dr.printPriceData();

//   Simulator::runSimulation(configFile, inputDataFile, outputFile);

  return 0;
}
