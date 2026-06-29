#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <iostream>
using namespace boost::accumulators;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  // Define an accumulator set for calculating the mean and the
  // 2nd moment ...
  accumulator_set<double, stats<tag::mean, tag::moment<2>>> acc;

  // push in some data ...
  acc(1.2);
  acc(2.3);
  acc(3.4);
  acc(4.5);

  // Display the results ...
  std::cout << "Mean:   " << mean(acc) << std::endl;
  std::cout << "Moment: " << moment<2>(acc) << std::endl;

  return 0;
}
