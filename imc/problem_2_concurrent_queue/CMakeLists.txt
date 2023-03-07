cmake_minimum_required(VERSION 3.7)

project(concurrent_queue VERSION 0.1 LANGUAGES CXX)

message(status "***pre-build*** ${PROJECT_SOURCE_DIR}")

# if(UNIX)
if(DARWIN)
    message(status "Building on MacOS")
else(DARWIN)
    message(status "Building on an unsupported/untested platform.")
endif(DARWIN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weff")
add_executable(target ConcurrentQueue.cpp)
