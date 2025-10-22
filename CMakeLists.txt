cmake_minimum_required(VERSION 3.30 )

project(phyllanthus-emblica VERSION 0.1 LANGUAGES CXX)

message(STATUS "***pre-build*** ${PROJECT_NAME}. building with cmake version: ${CMAKE_VERSION}")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "Building on Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	message(STATUS "Building on Mac")
else()
	message(STATUS "Building on an unsupported/untested platform.")
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # if the compiler is of older version and cannot support cpp 23 feature build. This will indicate a cmake errro at this step.
set(CMAKE_EXTENSIONS OFF) # favour portability over minior compiler specific feature gains.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})

add_subdirectory(interview-experience)
add_subdirectory(playground)
add_subdirectory(extras)

# better to move it ot a function.
message("cpp features supported by the available compiler: \n")
foreach(feature ${CMAKE_CXX_COMPILE_FEATURES})
	message(${feature})
endforeach(feature)

# @TODO:
# 1-> review goldman_sachs, trc, sc, imc, jpmc
# 1-> solve jump, lhft, trading_tech, sq_capital etc
# 2-> add amazon_embedded, edgeverve, miscellaneous directories to the build remove flipkart's problem.
