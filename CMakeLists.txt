cmake_minimum_required(VERSION 4.00 )

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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})

add_subdirectory(interview-experience)
add_subdirectory(playground)
add_subdirectory(extras)
add_subdirectory(prep)

# ---- clang-format: on-demand 'format' / 'format-check' targets ----
# Deliberately NOT part of the default (ALL) build: formatting mutates source
# files, which would make `cmake --build` non-reproducible and race under -j.
# Invoke explicitly:  cmake --build <dir> --target format      (rewrites files)
#                     cmake --build <dir> --target format-check (CI, read-only)
find_program(CLANG_FORMAT_EXE NAMES clang-format clang-format-22 clang-format-21)
if(CLANG_FORMAT_EXE)
	file(GLOB_RECURSE PE_FORMAT_SOURCES CONFIGURE_DEPENDS
		${CMAKE_SOURCE_DIR}/interview-experience/*.cpp
		${CMAKE_SOURCE_DIR}/interview-experience/*.hpp
		${CMAKE_SOURCE_DIR}/interview-experience/*.h
		${CMAKE_SOURCE_DIR}/playground/*.cpp
		${CMAKE_SOURCE_DIR}/playground/*.hpp
		${CMAKE_SOURCE_DIR}/playground/*.h
		${CMAKE_SOURCE_DIR}/extras/*.cpp
		${CMAKE_SOURCE_DIR}/extras/*.hpp
		${CMAKE_SOURCE_DIR}/extras/*.h
		${CMAKE_SOURCE_DIR}/prep/*.cpp
		${CMAKE_SOURCE_DIR}/prep/*.hpp
		${CMAKE_SOURCE_DIR}/prep/*.h
		${CMAKE_SOURCE_DIR}/buinftech/*.cpp
		${CMAKE_SOURCE_DIR}/buinftech/*.hpp
		${CMAKE_SOURCE_DIR}/buinftech/*.h)
	# Defensive: never format anything that leaks in from the build tree.
	list(FILTER PE_FORMAT_SOURCES EXCLUDE REGEX "/build/")

	add_custom_target(format
		COMMAND ${CLANG_FORMAT_EXE} -i --style=file ${PE_FORMAT_SOURCES}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Formatting all sources in place with clang-format (Google style)"
		VERBATIM)

	add_custom_target(format-check
		COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror --style=file ${PE_FORMAT_SOURCES}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Checking formatting with clang-format (no files modified)"
		VERBATIM)

	message(STATUS "clang-format: ${CLANG_FORMAT_EXE} -> targets 'format' / 'format-check' enabled")
else()
	message(STATUS "clang-format not found -> 'format' / 'format-check' targets disabled")
endif()

# better to move it ot a function.
message("cpp features supported by the available compiler: \n")
foreach(feature ${CMAKE_CXX_COMPILE_FEATURES})
	message(${feature})
endforeach(feature)

# @TODO:
# 1-> review goldman_sachs, trc, sc, imc, jpmc
# 1-> solve jump, lhft, trading_tech, sq_capital etc
# 2-> add amazon_embedded, edgeverve, miscellaneous directories to the build remove flipkart's problem.
