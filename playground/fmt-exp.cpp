#include <cmath>
#include <fmt/color.h>
#include <fmt/format.h>
#include <iostream>
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  fmt::print("hello world\n");
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      // fmt works on replacements... indicated by {}
      fmt::print("j: {1} & i: {0}\t", i, j);
    }
  }

  fmt::print(fmt::fg(fmt::color::green) | fmt::bg(fmt::color::black),
             "hello world \n");

  auto fmtstr =
      fmt::format(fmt::fg(fmt::color::purple) | fmt::bg(fmt::color::black),
                  "hello fmt-formatted string. \n");
  std::cout << fmtstr << std::endl;

  // demo primitive type functions:
  fmt::print("fabs(-3.14): {} \n", fabs(-3.14));
  fmt::print("abs(-3.14): {} \n", abs(-3.14));

  fmt::print("size_of(unsigned long long): {}", sizeof(unsigned long long));
  fmt::print("size_of(unsigned long long) in bits: {}",
             8 * sizeof(unsigned long long));
  return 0;
}
