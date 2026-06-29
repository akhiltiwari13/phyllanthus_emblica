#include <asio.hpp>
#include <asio/detail/chrono.hpp>
#include <asio/placeholders.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <system_error>

void funct_with_args([[maybe_unused]] const std::error_code& e,
                     asio::steady_timer* t, int* count) {
  if (*count < 5) {
    std::cout << *count << std::endl;
    ++(*count);
  }

  t->expires_at(t->expiry() + asio::chrono::seconds(2));
  t->async_wait(
      std::bind(funct_with_args, asio::placeholders::error, t, count));
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  asio::io_context ioc;

  // example3 binding args to completion handlers.
  int sec = 3;
  int count{0};
  asio::steady_timer tasyncbind(ioc, std::chrono::seconds(sec));
  tasyncbind.async_wait(std::bind(funct_with_args, asio::placeholders::error,
                                  &tasyncbind, &count));
  ioc.run();
  std::cout << "The Final Count is: " << count << std::endl;
  return 0;
}
