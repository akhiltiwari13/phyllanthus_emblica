# @TODO: This playground is excluded from cmake build dirs. All the link/include/execution errors needs to be removed first before adding this to the code.

# add_executable(crtp crtp.cpp)
# add_executable(comm-infra-example comm_infra.cpp)
# target_link_libraries(comm-infra-example PRIVATE infra-events )
# add_executable(vfunc virtual_funcs.cpp)
# add_executable(vfunc virtual_funcs.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Tracy REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

# add_executable(tracy_example tracy_example.cpp )
# target_include_directories(tracy_example
# PRIVATE
# 		$<INSTALL_INTERFACE:include>                             # For installed packages
# 		${Tracy_INCLUDE_DIRS})

# @TODO: FIXIT. this introduces linking error with tracy
# target_compile_definitions(tracy_example PUBLIC TRACY_ENABLE=1)
# target_link_libraries(tracy_example PRIVATE Tracy::TracyClient ${CMAKE_DL_LIBS} Threads::Threads)

# include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

# Boost
add_executable(boost_usage boost_usage.cpp)
target_link_libraries(boost_usage PUBLIC boost::boost)

add_executable(boost_asio boost_asio.cpp)
target_link_libraries(boost_asio PUBLIC boost::boost)

# Cap'n Proto
# @TODO: has linking error Cap'n Proto.
# find_package(CapnProto REQUIRED)
# add_executable(capnproto_usage capnproto_usage.cpp)
# target_include_directories( capnproto_usage PRIVATE $<BUILD_INTERFACE:${CapnProto_INCLUDE_DIRS}>)
# target_link_libraries(capnproto_usage PUBLIC CapnProto::capnp)

# # Cereal
# find_package(cereal REQUIRED)
# add_executable(cereal_usage cereal_usage.cpp)
# target_include_directories( cereal_usage PRIVATE $<BUILD_INTERFACE:${cereal_INCLUDE_DIRS}>)
# target_link_libraries(cereal_usage PUBLIC cereal::cereal)
#
# # CryptoPP
# # find_package(CryptoPP REQUIRED)
# # add_executable(cryptopp_usage cryptopp_usage.cpp)
# # target_link_libraries(cryptopp_usage PUBLIC CryptoPP::CryptoPP)
#
# # fmt
# find_package(fmt REQUIRED)
# add_executable(fmt_usage fmt_usage.cpp)
# target_link_libraries(fmt_usage PUBLIC fmt::fmt)
#
# # folly
# find_package(folly REQUIRED)
# add_executable(folly_usage folly_usage.cpp)
# target_link_libraries(folly_usage PUBLIC folly::folly)
#
# # magic_enum
# find_package(magic_enum REQUIRED)
# add_executable(magic_enum_usage magic_enum_usage.cpp)
# target_link_libraries(magic_enum_usage PUBLIC magic_enum::magic_enum)
#
# # nlohmann_json
# find_package(nlohmann_json REQUIRED)
# add_executable(nlohmann_usage nlohmann_usage.cpp)
# target_link_libraries(nlohmann_usage PUBLIC nlohmann_json::nlohmann_json)
#
# # spdlog
# find_package(spdlog REQUIRED)
# add_executable(spdlog_usage spdlog_usage.cpp)
# target_link_libraries(spdlog_usage PUBLIC spdlog::spdlog)
#
# # Tracy
# # find_package(tracy REQUIRED)
# # add_executable(tracy_usage tracy_usage.cpp)
# # target_link_libraries(tracy_usage PUBLIC tracy::tracy)
#
# # YAML-CPP
# find_package(yaml-cpp REQUIRED)
# add_executable(yaml_usage yaml_usage.cpp)
# target_link_libraries(yaml_usage PUBLIC yaml-cpp)
