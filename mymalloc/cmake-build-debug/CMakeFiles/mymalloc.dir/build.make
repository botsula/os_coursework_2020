# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/botsula/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/botsula/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mymalloc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mymalloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mymalloc.dir/flags.make

CMakeFiles/mymalloc.dir/main.c.o: CMakeFiles/mymalloc.dir/flags.make
CMakeFiles/mymalloc.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mymalloc.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mymalloc.dir/main.c.o   -c /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/main.c

CMakeFiles/mymalloc.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mymalloc.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/main.c > CMakeFiles/mymalloc.dir/main.c.i

CMakeFiles/mymalloc.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mymalloc.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/main.c -o CMakeFiles/mymalloc.dir/main.c.s

# Object files for target mymalloc
mymalloc_OBJECTS = \
"CMakeFiles/mymalloc.dir/main.c.o"

# External object files for target mymalloc
mymalloc_EXTERNAL_OBJECTS =

mymalloc: CMakeFiles/mymalloc.dir/main.c.o
mymalloc: CMakeFiles/mymalloc.dir/build.make
mymalloc: CMakeFiles/mymalloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mymalloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymalloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mymalloc.dir/build: mymalloc

.PHONY : CMakeFiles/mymalloc.dir/build

CMakeFiles/mymalloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mymalloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mymalloc.dir/clean

CMakeFiles/mymalloc.dir/depend:
	cd /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug /home/botsula/STUDY/OS/COURSE/git/os_coursework_2020/mymalloc/cmake-build-debug/CMakeFiles/mymalloc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mymalloc.dir/depend

