cmake_minimum_required(VERSION 3.20)


set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ConfigParser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/simulator.cpp)
add_executable(simulator ${SOURCES})
target_include_directories(simulator PUBLIC ${YAML_CPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(simulator yaml-cpp csv_parser strats)

# Once the build completes, copy config & input files to the binary directory
add_custom_command(
    TARGET simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_SOURCE_DIR}/input_files $<TARGET_FILE_DIR:simulator>
)

