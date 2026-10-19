#include <print>
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  std::println("hello world!");
  // std::alignas()
  [[maybe_unused]] auto x{std::hardware_destructive_interference_size};
  return 0;
}
