cmake_minimum_required(VERSION 3.7)

add_library(csv-parser INTERFACE)
target_include_directories(csv-parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
