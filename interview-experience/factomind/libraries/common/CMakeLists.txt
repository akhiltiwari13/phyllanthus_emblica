add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h)

add_library(time_series_data SHARED ${CMAKE_CURRENT_SOURCE_DIR}/TimeSeriesData.cpp)
target_include_directories(time_series_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
