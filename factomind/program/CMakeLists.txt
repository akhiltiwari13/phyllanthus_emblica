cmake_minimum_required(VERSION 3.7)

add_executable(cfg_parser cfg_parser.cpp)
target_include_directories(cfg_parser PUBLIC ${YAML_CPP_INCLUDE_DIR})
target_link_libraries(cfg_parser yaml-cpp)


add_executable(simulator ${CMAKE_CURRENT_SOURCE_DIR}/simulator.cpp)
target_include_directories(simulator PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(simulator yaml-cpp csv-parser)
