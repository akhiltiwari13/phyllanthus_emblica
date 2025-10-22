add_library(data_reader SHARED ${CMAKE_CURRENT_SOURCE_DIR}/DataReader.cpp)
target_include_directories(data_reader PUBLIC ${YAML_CPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data_reader yaml-cpp ${Boost_LIBRARIES})