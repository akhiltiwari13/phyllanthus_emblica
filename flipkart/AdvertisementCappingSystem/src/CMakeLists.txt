set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(ad_cap main.cpp)

target_link_libraries(ad_cap PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(ad_cap PRIVATE ${INCLUDE_DIRS})



