cmake_minimum_required(VERSION 3.30 )

project(testproj VERSION 0.1 LANGUAGES CXX)

message(STATUS "***pre-build*** ${PROJECT_NAME}. building with cmake version: ${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # if the compiler is of older version and cannot support cpp 23 feature build. This will indicate a cmake errro at this step.
set(CMAKE_EXTENSIONS OFF) # favour portability over minior compiler specific feature gains.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

add_executable(testp producer_consumer.cpp)
