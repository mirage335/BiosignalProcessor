cmake_minimum_required (VERSION 2.6) # Required cmake version.
project (PROJECT_NAME)	#BiosignalProcessor Name

# Colorize GCC output. Taken from http://stackoverflow.com/questions/14399984/make-cmake-use-gccfilter . Public domain or fair use assumed.
set_directory_properties(PROPERTIES RULE_LAUNCH_COMPILE
   "${PROJECT_SOURCE_DIR}/gccfilter_wrap")

#Default CMAKE_GENERATOR should be the quite standard and ubiquitous Unix Makefiles.
if(NOT(DEFINED CMAKE_GENERATOR))
SET(CMAKE_GENERATOR "Unix Makefiles")
endif(NOT(DEFINED CMAKE_GENERATOR))

# Set default compiler flags for extra warnings in eclipse-friendly format.
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fmessage-length=0")

# Set compiler flags used for debugging.
SET(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG -DVERBOSE")

# Set compiler flags for pedantic compilation.
SET (CMAKE_C_FLAGS_PEDANTIC "-g -pedantic")

#Allow eclipse to discover include directories.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Find dependencies.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
find_package (LibSndFile)

# Process CMakeLists files in these subdirectories.
add_subdirectory (include)
add_subdirectory (src)
