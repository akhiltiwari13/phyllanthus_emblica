cmake_minimum_required(VERSION 3.27)

project(PhyllanthusEmblica VERSION 0.1 LANGUAGES CXX)

message(status "***pre-build*** ${PROJECT_SOURCE_DIR}")

if(UNIX)
  message(status "Building on Linux/Unix")
else()
  message(status "Building on an unsupported/untested platform.")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  include_directories(${CMAKE_SOURCE_DIR}/osx_inc/)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory(jump_trading)
add_subdirectory(goldman_sachs)
add_subdirectory(tower_research_capital)
add_subdirectory(optiver)
add_subdirectory(trading_technologies)
add_subdirectory(standard_chartered)
add_subdirectory(squarepoint-capital)
add_subdirectory(millenium)
add_subdirectory(edgeverve)
add_subdirectory(imc)
add_subdirectory(jpmc)
add_subdirectory(aargo_trade)
add_subdirectory(ogha)
# add_subdirectory(factomind)
add_subdirectory(greenland_investment_mgmt)
# add_subdirectory(trexquant)
# add_subdirectory(alphagrep)
# add_subdirectory(lhft)
add_subdirectory(amazon_embedded)
add_subdirectory(miscellaneous)
add_executable(greenland circ_buff.cpp)

# @TODO:
# 1-> review goldman_sachs, trc, sc, imc, jpmc
# 1-> solve jump, lhft, trading_tech, sq_capital etc
# 2-> add amazon_embedded, edgeverve, miscellaneous directories to the build remove flipkart's problem.
