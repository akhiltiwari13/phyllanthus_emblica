#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  io_service ioservice;
  steady_timer timer{ioservice, std::chrono::seconds{3}};
  timer.async_wait(
      []([[maybe_unused]] const boost::system::error_code &ec) { std::cout << "3 sec\n"; });
  ioservice.run();
  return 0;
}
