cmake_minimum_required(VERSION 3.20)

project(HoldingPositionSimulator VERSION 1.0 LANGUAGES CXX)

message(status "***pre-build*** ${PROJECT_SOURCE_DIR}")


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(status "Building on Mac OSX")
else()
    message(status "Building on an unsupported/untested platform.")
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

find_package(yaml-cpp REQUIRED)
find_package(Boost COMPONENTS log date_time REQUIRED )

include_directories(${Boost_INCLUDE_DIRS})
include_directories(libraries)

add_subdirectory(libraries)
# add_subdirectory(programs)

