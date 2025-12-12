
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <iostream>
#include <string>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  boost::property_tree::ptree pt;

  // ptree expects . as a separator for it's keys
  pt.put("home.quomptrade.Work", "5 files");
  boost::property_tree::ptree &home = pt.get_child("home");
  boost::property_tree::ptree &quompt = home.get_child("quomptrade");
  boost::property_tree::ptree &work = quompt.get_child("Work");

  std::cout << work.get_value<std::string>() << std::endl;
  // std::cout << quompt.get_value<std::string>() << std::endl;

  boost::property_tree::basic_ptree<std::string, int> bpt;
  bpt.put(boost::property_tree::ptree::path_type{"home/quomptrade/Work", '/'},
          15);
  bpt.put(
      boost::property_tree::ptree::path_type{"home/quomptrade/.config", '/'},
      33);
  for (auto node : pt) {
    std::cout << "node: " << node.second.get_value<std::string>() << std::endl;
  }

  auto qpt = bpt.get_child(
      boost::property_tree::ptree::path_type{"home/quomptrade", '/'});
  for (auto node : qpt) {
    std::cout << "node.first: " << node.first
              << " node.second: " << node.second.get_value<int>() << std::endl;
  }
  return 0;
}
