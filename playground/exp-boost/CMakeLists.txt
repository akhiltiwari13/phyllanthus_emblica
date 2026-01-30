find_package(Boost REQUIRED COMPONENTS boost headers)

# TODO:: don't link all boost libs to executable, just the required componnets.
add_executable(boost_asio boost_asio.cpp)
target_link_libraries(boost_asio Boost::boost)


add_executable(boost_ipc boost_ipc.cpp)
target_link_libraries(boost_ipc Boost::boost)
# target_link_libraries(boost_ipc Boost::interprocess)

add_executable(boost_ptree boost_ptree.cpp)
target_link_libraries(boost_ptree Boost::boost)

# add_executable(boost_accumulators boost_accumulators.cpp)
# target_link_libraries(boost_accumulators Boost::boost)

# add_executable(boost_logging boost_logging.cpp)
# target_link_libraries(boost_logging Boost::headers)
