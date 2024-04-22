cmake_minimum_required(VERSION 3.20)


# ${CMAKE_CURRENT_SOURCE_DIR}/OutputWriter.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/Simulator.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/TradingAlgo.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/ConfigParser.cpp 

set(SOURCES 
${CMAKE_CURRENT_SOURCE_DIR}/DataReader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(simulator ${SOURCES})
target_include_directories(simulator PUBLIC ${YAML_CPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(simulator ${Boost_LIBRARIES} yaml-cpp  strats cfg_parser)

# Once the build completes, copy config & input files to the binary directory
add_custom_command(
    TARGET simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_SOURCE_DIR}/input_files $<TARGET_FILE_DIR:simulator>
)

# target_link_libraries(simulator Boost::log  Boost::date_time yaml-cpp  strats)
# target_link_libraries(simulator  yaml-cpp csv_parser strats)

