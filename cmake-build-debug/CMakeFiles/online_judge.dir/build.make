# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /opt/clion-2017.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tansei/online-judge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tansei/online-judge/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/online_judge.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/online_judge.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/online_judge.dir/flags.make

CMakeFiles/online_judge.dir/qtree/qtree.cc.o: CMakeFiles/online_judge.dir/flags.make
CMakeFiles/online_judge.dir/qtree/qtree.cc.o: ../qtree/qtree.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tansei/online-judge/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/online_judge.dir/qtree/qtree.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/online_judge.dir/qtree/qtree.cc.o -c /home/tansei/online-judge/qtree/qtree.cc

CMakeFiles/online_judge.dir/qtree/qtree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/online_judge.dir/qtree/qtree.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tansei/online-judge/qtree/qtree.cc > CMakeFiles/online_judge.dir/qtree/qtree.cc.i

CMakeFiles/online_judge.dir/qtree/qtree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/online_judge.dir/qtree/qtree.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tansei/online-judge/qtree/qtree.cc -o CMakeFiles/online_judge.dir/qtree/qtree.cc.s

CMakeFiles/online_judge.dir/qtree/qtree.cc.o.requires:

.PHONY : CMakeFiles/online_judge.dir/qtree/qtree.cc.o.requires

CMakeFiles/online_judge.dir/qtree/qtree.cc.o.provides: CMakeFiles/online_judge.dir/qtree/qtree.cc.o.requires
	$(MAKE) -f CMakeFiles/online_judge.dir/build.make CMakeFiles/online_judge.dir/qtree/qtree.cc.o.provides.build
.PHONY : CMakeFiles/online_judge.dir/qtree/qtree.cc.o.provides

CMakeFiles/online_judge.dir/qtree/qtree.cc.o.provides.build: CMakeFiles/online_judge.dir/qtree/qtree.cc.o


# Object files for target online_judge
online_judge_OBJECTS = \
"CMakeFiles/online_judge.dir/qtree/qtree.cc.o"

# External object files for target online_judge
online_judge_EXTERNAL_OBJECTS =

online_judge: CMakeFiles/online_judge.dir/qtree/qtree.cc.o
online_judge: CMakeFiles/online_judge.dir/build.make
online_judge: CMakeFiles/online_judge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tansei/online-judge/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable online_judge"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/online_judge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/online_judge.dir/build: online_judge

.PHONY : CMakeFiles/online_judge.dir/build

CMakeFiles/online_judge.dir/requires: CMakeFiles/online_judge.dir/qtree/qtree.cc.o.requires

.PHONY : CMakeFiles/online_judge.dir/requires

CMakeFiles/online_judge.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/online_judge.dir/cmake_clean.cmake
.PHONY : CMakeFiles/online_judge.dir/clean

CMakeFiles/online_judge.dir/depend:
	cd /home/tansei/online-judge/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tansei/online-judge /home/tansei/online-judge /home/tansei/online-judge/cmake-build-debug /home/tansei/online-judge/cmake-build-debug /home/tansei/online-judge/cmake-build-debug/CMakeFiles/online_judge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/online_judge.dir/depend

