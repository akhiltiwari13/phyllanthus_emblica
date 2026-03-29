# AGENTS.md - Coding Agent Guidelines

This document provides guidelines for AI coding agents working in the Phyllanthus Emblica codebase.

## Project Overview

A collection of HFT/Quant interview questions and coding assignments implemented in C++23.
The codebase follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

## Build System

### Requirements
- CMake 3.30+
- Conan 2.x (package manager)
- GCC 15 (Linux/Fedora) or Clang 20 (macOS ARM)
- C++23 standard

### Dependencies (via Conan)
- boost/~1.88
- yaml-cpp/>=0.8.0
- fmt/~12.0
- nlohmann_json/>=3.12.0
- benchmark/>=1.8.5
- gtest/>=1.16.0
- tracy/~0.13

### Build Commands

```bash
# Install Conan dependencies (Linux Debug)
conan install . --profile=conan/conan-profiles/debug-fedora-x86-gcc --build=missing

# Configure CMake with Conan preset
cmake --preset conan-debug

# Build all targets
cmake --build build/Debug

# Build a specific target
cmake --build build/Debug --target <target_name>
# Example: cmake --build build/Debug --target forest
```

### Available Conan Profiles
- `conan/conan-profiles/debug-fedora-x86-gcc` - Linux Debug (GCC 15)
- `conan/conan-profiles/default-fedora-x86-gcc` - Linux Release (GCC 15)
- `conan/conan-profiles/debug-mac-arm` - macOS ARM Debug (Clang 20)
- `conan/conan-profiles/default-mac-arm` - macOS ARM Release

### Running Individual Executables

```bash
# After building, run individual problem solutions
./build/Debug/interview-experience/<company>/<executable>

# Example
./build/Debug/interview-experience/goldman_sachs/forest
```

## Testing

Most solutions use inline test functions rather than a separate test framework:

```cpp
bool doTestsPass() {
    // Test cases defined inline
    bool passed = true;
    // ... validation logic
    return passed;
}

int main() {
    if (doTestsPass()) {
        std::cout << "ALL TESTS PASS." << std::endl;
    } else {
        std::cout << "TESTS FAILED." << std::endl;
    }
    return 0;
}
```

Google Test is available via Conan but not widely used yet.

## Linting

No `.clang-format` or `.clang-tidy` files exist. Linting relies on strict compiler warnings:

```cmake
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
```

All warnings are treated as errors. Fix all compiler warnings before committing.

## Code Style Guidelines

### Naming Conventions
- **Classes**: `PascalCase` (e.g., `ConcurrentQueue`, `VersionQueue`, `RPS`)
- **Functions**: `camelCase` or `PascalCase` (e.g., `genSystemMove()`, `GetCurrentVersion()`)
- **Variables**: `snake_case` (e.g., `min_diff`, `current_version_`)
- **Member variables**: `_prefix` or `suffix_` (e.g., `_reps`, `front_`, `mReadPtr`)
- **Constants/Template params**: `SCREAMING_SNAKE_CASE` or `PascalCase`
- **Namespaces**: `snake_case`, nested allowed (e.g., `namespace imc::rps`)

### Header Guards
Use `#pragma once` (preferred) or traditional guards:
```cpp
#pragma once
// or
#ifndef MY_HEADER_H
#define MY_HEADER_H
// ...
#endif
```

### Include Order
1. Corresponding header file (for .cpp files)
2. C++ standard library headers
3. Third-party library headers (Boost, fmt, etc.)
4. Project headers

```cpp
#include "rps.h"          // Corresponding header first
#include <iostream>       // Standard library
#include <string>
#include <boost/log.hpp>  // Third-party
#include "common/utils.h" // Project headers
```

### Documentation Style
Use Doxygen-style comments for file headers and public APIs:
```cpp
/**
 * @file rps.cpp
 * @author akhil tiwari (akhiltiwari.13@gmail.com)
 * @brief Brief description
 * @version 0.1
 * @date 2023-03-09
 * @copyright Copyright (c) 2023
 */
```

### Namespaces
- Use nested namespaces: `namespace company::module { }`
- Avoid `using namespace std;` in headers
- Close namespace with comment: `} // namespace imc::rps`

### Error Handling
Use standard exceptions for error conditions:
```cpp
throw std::runtime_error("Queue full - cannot write!");
throw std::out_of_range("Index out of bounds");
throw std::invalid_argument("Invalid parameter value");
```

For interview problem input errors, use exit codes with error messages:
```cpp
std::cout << "E1" << std::endl;  // Input syntax error
exit(0);
```

### Type Usage
- Prefer `uint64_t`, `int64_t` over `unsigned long`, `long`
- Use `auto` for complex iterator types and lambdas
- Use `const` and `constexpr` wherever appropriate
- Use `std::string_view` for non-owning string references

### Modern C++ Features (C++23)
- Use range-based for loops
- Prefer smart pointers over raw pointers for ownership
- Use `std::optional`, `std::variant` where appropriate
- Use structured bindings: `auto [key, value] = pair;`
- Use `constexpr` for compile-time computation

### Class Design
```cpp
class MyClass {
public:
    // Constructors first
    MyClass();
    explicit MyClass(int value);
    
    // Public methods
    void publicMethod();
    
private:
    // Member variables with underscore prefix or suffix
    int _value;
    std::string name_;
};
```

## Project Structure

```
phyllanthus_emblica/
├── CMakeLists.txt              # Root CMake configuration
├── conanfile.py                # Conan package configuration
├── conan/conan-profiles/       # Build profiles
├── interview-experience/       # Main source code
│   ├── <company_name>/         # Per-company solutions
│   │   ├── CMakeLists.txt
│   │   └── *.cpp, *.h
├── playground/                 # Experimentation area
├── extras/                     # Additional code snippets
└── problems/                   # Problem statements/images
```

## Adding New Solutions

1. Create directory under `interview-experience/<company_name>/`
2. Add `CMakeLists.txt` with executable target:
   ```cmake
   add_executable(target_name source.cpp)
   ```
3. Include subdirectory in parent `CMakeLists.txt`:
   ```cmake
   add_subdirectory(company_name)
   ```
4. Include inline tests using `doTestsPass()` pattern
5. Ensure code compiles with `-Wall -Wextra -Wpedantic -Werror`

## Important Notes

- In-source builds are forbidden (use `build/` directory)
- LTO (Link Time Optimization) is enabled when supported
- Compiler extensions are disabled for portability
- All code must compile without warnings (warnings are errors)
