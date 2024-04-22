add_library(csv_parser INTERFACE)

add_library(strats SHARED ${CMAKE_CURRENT_SOURCE_DIR}/strats/TradingStrategy.cpp)
add_subdirectory(config_parser)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

