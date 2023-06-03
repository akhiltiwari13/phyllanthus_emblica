cmake_minimum_required(VERSION 3.7)

project(HoldingsSimulator VERSION 0.1 LANGUAGES CXX)

message(status "***pre-build*** ${PROJECT_SOURCE_DIR}")


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(status "Building on Mac OSX")
else()
    message(status "Building on an unsupported/untested platform.")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")


find_package(yaml-cpp REQUIRED)


# add_subdirectory(src)
# add_subdirectory(test)
add_subdirectory(lib)
add_subdirectory(program)
