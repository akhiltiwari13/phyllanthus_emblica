find_package(Boost REQUIRED)

add_executable(boost_asio boost_asio.cpp)
target_link_libraries(boost_asio boost::boost)


add_executable(boost_ipc boost_ipc.cpp)
target_link_libraries(boost_ipc boost::boost)
