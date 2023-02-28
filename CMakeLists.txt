cmake_minimum_required(VERSION 3.7)

project(PhyllanthusEmblica VERSION 0.1 LANGUAGES CXX)

message(status "***pre-build*** ${PROJECT_SOURCE_DIR}")

if(UNIX)
    message(status "Building on Linux/Unix")
else(UNIX)
    message(status "Building on an unsupported/untested platform.")
endif(UNIX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory(jump_trading)
add_subdirectory(goldman_sachs)
add_subdirectory(lhft)
add_subdirectory(tower_research_capital)
add_subdirectory(optiver)
add_subdirectory(trading_technologies)
add_subdirectory(standard_chartered)
add_subdirectory(squarepoint_capital)
add_subdirectory(edgeverve)