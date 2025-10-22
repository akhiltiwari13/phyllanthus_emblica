include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(vqueue STATIC VersionQueue.cpp)

add_executable(vqdemo vqmain.cpp)
target_link_libraries(vqdemo vqueue)
