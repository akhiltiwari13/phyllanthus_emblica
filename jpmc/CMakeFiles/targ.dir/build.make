# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/akhil/files/projects/jpmc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/akhil/files/projects/jpmc

# Include any dependencies generated for this target.
include CMakeFiles/targ.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/targ.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/targ.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/targ.dir/flags.make

CMakeFiles/targ.dir/jpmctest.cpp.o: CMakeFiles/targ.dir/flags.make
CMakeFiles/targ.dir/jpmctest.cpp.o: jpmctest.cpp
CMakeFiles/targ.dir/jpmctest.cpp.o: CMakeFiles/targ.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/akhil/files/projects/jpmc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/targ.dir/jpmctest.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/targ.dir/jpmctest.cpp.o -MF CMakeFiles/targ.dir/jpmctest.cpp.o.d -o CMakeFiles/targ.dir/jpmctest.cpp.o -c /Users/akhil/files/projects/jpmc/jpmctest.cpp

CMakeFiles/targ.dir/jpmctest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/targ.dir/jpmctest.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/akhil/files/projects/jpmc/jpmctest.cpp > CMakeFiles/targ.dir/jpmctest.cpp.i

CMakeFiles/targ.dir/jpmctest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/targ.dir/jpmctest.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/akhil/files/projects/jpmc/jpmctest.cpp -o CMakeFiles/targ.dir/jpmctest.cpp.s

# Object files for target targ
targ_OBJECTS = \
"CMakeFiles/targ.dir/jpmctest.cpp.o"

# External object files for target targ
targ_EXTERNAL_OBJECTS =

targ: CMakeFiles/targ.dir/jpmctest.cpp.o
targ: CMakeFiles/targ.dir/build.make
targ: CMakeFiles/targ.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/akhil/files/projects/jpmc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable targ"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/targ.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/targ.dir/build: targ
.PHONY : CMakeFiles/targ.dir/build

CMakeFiles/targ.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/targ.dir/cmake_clean.cmake
.PHONY : CMakeFiles/targ.dir/clean

CMakeFiles/targ.dir/depend:
	cd /Users/akhil/files/projects/jpmc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/akhil/files/projects/jpmc /Users/akhil/files/projects/jpmc /Users/akhil/files/projects/jpmc /Users/akhil/files/projects/jpmc /Users/akhil/files/projects/jpmc/CMakeFiles/targ.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/targ.dir/depend
