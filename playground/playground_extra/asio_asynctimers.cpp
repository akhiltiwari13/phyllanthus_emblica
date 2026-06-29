#include <asio.hpp>
#include <asio/detail/chrono.hpp>
#include <asio/placeholders.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <print>
#include <system_error>
#include <thread>
#include <vector>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  asio::io_context ioc;
  int sec = 3;
  std::cout << "Hello World from main0." << std::endl;

  // example3. asynchronous timers
  std::vector<asio::steady_timer> timers;

  // multiple timers exeuted asynchronously.
  for (size_t i = 0; i < 5; i++) {
    asio::steady_timer tasync(ioc, std::chrono::seconds(sec));
    tasync.async_wait([]([[maybe_unused]] const std::error_code& e) -> void {
      std::println("print lambda: error_code{}", e.message());
      return;
    });  // non blocking wait
    // timers.push_back(tasync);//this doesn't work! why? @llm ask?
    timers.push_back(std::move(tasync));
  }
  ioc.run();
  std::cout << "Hello World from main1." << std::endl;

  return 0;
}
