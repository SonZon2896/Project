# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/547AF2557AF232FA/lessons/projects/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/547AF2557AF232FA/lessons/projects/Project/build

# Include any dependencies generated for this target.
include CMakeFiles/testing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testing.dir/flags.make

CMakeFiles/testing.dir/main.cpp.o: CMakeFiles/testing.dir/flags.make
CMakeFiles/testing.dir/main.cpp.o: ../main.cpp
CMakeFiles/testing.dir/main.cpp.o: CMakeFiles/testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/547AF2557AF232FA/lessons/projects/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testing.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testing.dir/main.cpp.o -MF CMakeFiles/testing.dir/main.cpp.o.d -o CMakeFiles/testing.dir/main.cpp.o -c /mnt/547AF2557AF232FA/lessons/projects/Project/main.cpp

CMakeFiles/testing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/547AF2557AF232FA/lessons/projects/Project/main.cpp > CMakeFiles/testing.dir/main.cpp.i

CMakeFiles/testing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/547AF2557AF232FA/lessons/projects/Project/main.cpp -o CMakeFiles/testing.dir/main.cpp.s

CMakeFiles/testing.dir/Cpp/Heads.cpp.o: CMakeFiles/testing.dir/flags.make
CMakeFiles/testing.dir/Cpp/Heads.cpp.o: ../Cpp/Heads.cpp
CMakeFiles/testing.dir/Cpp/Heads.cpp.o: CMakeFiles/testing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/547AF2557AF232FA/lessons/projects/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testing.dir/Cpp/Heads.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testing.dir/Cpp/Heads.cpp.o -MF CMakeFiles/testing.dir/Cpp/Heads.cpp.o.d -o CMakeFiles/testing.dir/Cpp/Heads.cpp.o -c /mnt/547AF2557AF232FA/lessons/projects/Project/Cpp/Heads.cpp

CMakeFiles/testing.dir/Cpp/Heads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing.dir/Cpp/Heads.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/547AF2557AF232FA/lessons/projects/Project/Cpp/Heads.cpp > CMakeFiles/testing.dir/Cpp/Heads.cpp.i

CMakeFiles/testing.dir/Cpp/Heads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing.dir/Cpp/Heads.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/547AF2557AF232FA/lessons/projects/Project/Cpp/Heads.cpp -o CMakeFiles/testing.dir/Cpp/Heads.cpp.s

# Object files for target testing
testing_OBJECTS = \
"CMakeFiles/testing.dir/main.cpp.o" \
"CMakeFiles/testing.dir/Cpp/Heads.cpp.o"

# External object files for target testing
testing_EXTERNAL_OBJECTS =

testing: CMakeFiles/testing.dir/main.cpp.o
testing: CMakeFiles/testing.dir/Cpp/Heads.cpp.o
testing: CMakeFiles/testing.dir/build.make
testing: CMakeFiles/testing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/547AF2557AF232FA/lessons/projects/Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testing.dir/build: testing
.PHONY : CMakeFiles/testing.dir/build

CMakeFiles/testing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testing.dir/clean

CMakeFiles/testing.dir/depend:
	cd /mnt/547AF2557AF232FA/lessons/projects/Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/547AF2557AF232FA/lessons/projects/Project /mnt/547AF2557AF232FA/lessons/projects/Project /mnt/547AF2557AF232FA/lessons/projects/Project/build /mnt/547AF2557AF232FA/lessons/projects/Project/build /mnt/547AF2557AF232FA/lessons/projects/Project/build/CMakeFiles/testing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testing.dir/depend

