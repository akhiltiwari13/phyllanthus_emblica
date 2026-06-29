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

void funct_with_nap([[maybe_unused]] const std::error_code& e) {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "Hello World, from funct after a nap()" << std::endl;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  asio::io_context ioc;

  int sec = 3;

  // example1. synchronous timer
  asio::steady_timer t(ioc, std::chrono::seconds(sec));
  t.wait();  // blocking wait
  // ioc run is not needed in the sync timer.
  std::cout << "Hello World from main0." << std::endl;

  // example2. asynchronous timer
  // The asio library provides a guarantee that completion handlers will only be
  // called from threads that are currently calling asio::io_context::run().
  // Therefore unless the asio::io_context::run() function is called the
  // completion handler for the asynchronous wait completion will never be
  // invoked. The asio::io_context::run() function will also continue to run
  // while there is still "work" to do. In this example, the work is the
  // asynchronous wait on the timer, so the call will not return until the timer
  // has expired and the completion handler has returned.
  asio::steady_timer tasync(ioc, std::chrono::seconds(5));
  tasync.async_wait(&funct_with_nap);  // non blocking wait
  ioc.run();
  std::cout << "Hello World from main1." << std::endl;

  return 0;
}
