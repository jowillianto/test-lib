# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jonathanwillianto/Documents/Projects/test-lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jonathanwillianto/Documents/Projects/test-lib/build

# Include any dependencies generated for this target.
include CMakeFiles/test-lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test-lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test-lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-lib.dir/flags.make

CMakeFiles/test-lib.dir/src/test-lib.cpp.o: CMakeFiles/test-lib.dir/flags.make
CMakeFiles/test-lib.dir/src/test-lib.cpp.o: /Users/jonathanwillianto/Documents/Projects/test-lib/src/test-lib.cpp
CMakeFiles/test-lib.dir/src/test-lib.cpp.o: CMakeFiles/test-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/jonathanwillianto/Documents/Projects/test-lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test-lib.dir/src/test-lib.cpp.o"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test-lib.dir/src/test-lib.cpp.o -MF CMakeFiles/test-lib.dir/src/test-lib.cpp.o.d -o CMakeFiles/test-lib.dir/src/test-lib.cpp.o -c /Users/jonathanwillianto/Documents/Projects/test-lib/src/test-lib.cpp

CMakeFiles/test-lib.dir/src/test-lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test-lib.dir/src/test-lib.cpp.i"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jonathanwillianto/Documents/Projects/test-lib/src/test-lib.cpp > CMakeFiles/test-lib.dir/src/test-lib.cpp.i

CMakeFiles/test-lib.dir/src/test-lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test-lib.dir/src/test-lib.cpp.s"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jonathanwillianto/Documents/Projects/test-lib/src/test-lib.cpp -o CMakeFiles/test-lib.dir/src/test-lib.cpp.s

CMakeFiles/test-lib.dir/src/random.cpp.o: CMakeFiles/test-lib.dir/flags.make
CMakeFiles/test-lib.dir/src/random.cpp.o: /Users/jonathanwillianto/Documents/Projects/test-lib/src/random.cpp
CMakeFiles/test-lib.dir/src/random.cpp.o: CMakeFiles/test-lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/jonathanwillianto/Documents/Projects/test-lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test-lib.dir/src/random.cpp.o"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test-lib.dir/src/random.cpp.o -MF CMakeFiles/test-lib.dir/src/random.cpp.o.d -o CMakeFiles/test-lib.dir/src/random.cpp.o -c /Users/jonathanwillianto/Documents/Projects/test-lib/src/random.cpp

CMakeFiles/test-lib.dir/src/random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test-lib.dir/src/random.cpp.i"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jonathanwillianto/Documents/Projects/test-lib/src/random.cpp > CMakeFiles/test-lib.dir/src/random.cpp.i

CMakeFiles/test-lib.dir/src/random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test-lib.dir/src/random.cpp.s"
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jonathanwillianto/Documents/Projects/test-lib/src/random.cpp -o CMakeFiles/test-lib.dir/src/random.cpp.s

# Object files for target test-lib
test__lib_OBJECTS = \
"CMakeFiles/test-lib.dir/src/test-lib.cpp.o" \
"CMakeFiles/test-lib.dir/src/random.cpp.o"

# External object files for target test-lib
test__lib_EXTERNAL_OBJECTS =

libtest-lib.a: CMakeFiles/test-lib.dir/src/test-lib.cpp.o
libtest-lib.a: CMakeFiles/test-lib.dir/src/random.cpp.o
libtest-lib.a: CMakeFiles/test-lib.dir/build.make
libtest-lib.a: CMakeFiles/test-lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/jonathanwillianto/Documents/Projects/test-lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtest-lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/test-lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-lib.dir/build: libtest-lib.a
.PHONY : CMakeFiles/test-lib.dir/build

CMakeFiles/test-lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-lib.dir/clean

CMakeFiles/test-lib.dir/depend:
	cd /Users/jonathanwillianto/Documents/Projects/test-lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jonathanwillianto/Documents/Projects/test-lib /Users/jonathanwillianto/Documents/Projects/test-lib /Users/jonathanwillianto/Documents/Projects/test-lib/build /Users/jonathanwillianto/Documents/Projects/test-lib/build /Users/jonathanwillianto/Documents/Projects/test-lib/build/CMakeFiles/test-lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test-lib.dir/depend

