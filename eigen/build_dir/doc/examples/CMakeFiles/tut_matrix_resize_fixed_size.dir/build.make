# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/magshimim/Documents/exit-scan/eigen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/magshimim/Documents/exit-scan/eigen/build_dir

# Include any dependencies generated for this target.
include doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/depend.make

# Include the progress variables for this target.
include doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/progress.make

# Include the compile flags for this target's objects.
include doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/flags.make

doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o: doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/flags.make
doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o: ../doc/examples/tut_matrix_resize_fixed_size.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magshimim/Documents/exit-scan/eigen/build_dir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o"
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o -c /home/magshimim/Documents/exit-scan/eigen/doc/examples/tut_matrix_resize_fixed_size.cpp

doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.i"
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magshimim/Documents/exit-scan/eigen/doc/examples/tut_matrix_resize_fixed_size.cpp > CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.i

doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.s"
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magshimim/Documents/exit-scan/eigen/doc/examples/tut_matrix_resize_fixed_size.cpp -o CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.s

# Object files for target tut_matrix_resize_fixed_size
tut_matrix_resize_fixed_size_OBJECTS = \
"CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o"

# External object files for target tut_matrix_resize_fixed_size
tut_matrix_resize_fixed_size_EXTERNAL_OBJECTS =

doc/examples/tut_matrix_resize_fixed_size: doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/tut_matrix_resize_fixed_size.cpp.o
doc/examples/tut_matrix_resize_fixed_size: doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/build.make
doc/examples/tut_matrix_resize_fixed_size: doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/magshimim/Documents/exit-scan/eigen/build_dir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tut_matrix_resize_fixed_size"
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tut_matrix_resize_fixed_size.dir/link.txt --verbose=$(VERBOSE)
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && ./tut_matrix_resize_fixed_size >/home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples/tut_matrix_resize_fixed_size.out

# Rule to build all files generated by this target.
doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/build: doc/examples/tut_matrix_resize_fixed_size

.PHONY : doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/build

doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/clean:
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples && $(CMAKE_COMMAND) -P CMakeFiles/tut_matrix_resize_fixed_size.dir/cmake_clean.cmake
.PHONY : doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/clean

doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/depend:
	cd /home/magshimim/Documents/exit-scan/eigen/build_dir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/magshimim/Documents/exit-scan/eigen /home/magshimim/Documents/exit-scan/eigen/doc/examples /home/magshimim/Documents/exit-scan/eigen/build_dir /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples /home/magshimim/Documents/exit-scan/eigen/build_dir/doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/examples/CMakeFiles/tut_matrix_resize_fixed_size.dir/depend
