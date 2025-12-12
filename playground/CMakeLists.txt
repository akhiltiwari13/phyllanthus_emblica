find_package(fmt  REQUIRED)
add_subdirectory(exp-boost)
add_executable(s_queue producer_consumer.cpp)

add_executable(fmt-exp fmt-exp.cpp)
target_link_libraries(fmt-exp fmt)
# add_subdirectory(exp-asio)
