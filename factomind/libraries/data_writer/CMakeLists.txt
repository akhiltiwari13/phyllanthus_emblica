add_library(cfg_parser SHARED ${CMAKE_CURRENT_SOURCE_DIR}/ConfigParser.cpp)
target_include_directories(cfg_parser PUBLIC ${YAML_CPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cfg_parser yaml-cpp ${Boost_LIBRARIES})