# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release

# Include any dependencies generated for this target.
include src/CMakeFiles/OutputObjectName.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/OutputObjectName.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/OutputObjectName.dir/flags.make

src/CMakeFiles/OutputObjectName.dir/source.c.o: src/CMakeFiles/OutputObjectName.dir/flags.make
src/CMakeFiles/OutputObjectName.dir/source.c.o: ../src/source.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/OutputObjectName.dir/source.c.o"
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/OutputObjectName.dir/source.c.o   -c /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/src/source.c

src/CMakeFiles/OutputObjectName.dir/source.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OutputObjectName.dir/source.c.i"
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/src/source.c > CMakeFiles/OutputObjectName.dir/source.c.i

src/CMakeFiles/OutputObjectName.dir/source.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OutputObjectName.dir/source.c.s"
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/src/source.c -o CMakeFiles/OutputObjectName.dir/source.c.s

src/CMakeFiles/OutputObjectName.dir/source.c.o.requires:
.PHONY : src/CMakeFiles/OutputObjectName.dir/source.c.o.requires

src/CMakeFiles/OutputObjectName.dir/source.c.o.provides: src/CMakeFiles/OutputObjectName.dir/source.c.o.requires
	$(MAKE) -f src/CMakeFiles/OutputObjectName.dir/build.make src/CMakeFiles/OutputObjectName.dir/source.c.o.provides.build
.PHONY : src/CMakeFiles/OutputObjectName.dir/source.c.o.provides

src/CMakeFiles/OutputObjectName.dir/source.c.o.provides.build: src/CMakeFiles/OutputObjectName.dir/source.c.o

# Object files for target OutputObjectName
OutputObjectName_OBJECTS = \
"CMakeFiles/OutputObjectName.dir/source.c.o"

# External object files for target OutputObjectName
OutputObjectName_EXTERNAL_OBJECTS =

src/OutputObjectName: src/CMakeFiles/OutputObjectName.dir/source.c.o
src/OutputObjectName: src/CMakeFiles/OutputObjectName.dir/build.make
src/OutputObjectName: src/CMakeFiles/OutputObjectName.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable OutputObjectName"
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OutputObjectName.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/OutputObjectName.dir/build: src/OutputObjectName
.PHONY : src/CMakeFiles/OutputObjectName.dir/build

src/CMakeFiles/OutputObjectName.dir/requires: src/CMakeFiles/OutputObjectName.dir/source.c.o.requires
.PHONY : src/CMakeFiles/OutputObjectName.dir/requires

src/CMakeFiles/OutputObjectName.dir/clean:
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src && $(CMAKE_COMMAND) -P CMakeFiles/OutputObjectName.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/OutputObjectName.dir/clean

src/CMakeFiles/OutputObjectName.dir/depend:
	cd /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/src /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src /home/commonadmin/FSGateway/Projects/Current/BiosignalProcessor/Code/Release/src/CMakeFiles/OutputObjectName.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/OutputObjectName.dir/depend

