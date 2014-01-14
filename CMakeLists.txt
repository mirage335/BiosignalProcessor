cmake_minimum_required (VERSION 2.6) # Required cmake version.
project (PROJECT_NAME)	#BiosignalProcessor Name

#Default CMAKE_GENERATOR should be the quite standard and ubiquitous Unix Makefiles.
if(NOT(DEFINED CMAKE_GENERATOR))
SET(CMAKE_GENERATOR "Unix Makefiles")
endif(NOT(DEFINED CMAKE_GENERATOR))

# Set default compiler flags for extra warnings in eclipse-friendly format.
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fmessage-length=0")

# Set compiler flags used for debugging.
SET(CMAKE_C_FLAGS_DEBUG "-DDEBUG -DVERBOSE")

# Set compiler flags for pedantic compilation.
SET (CMAKE_C_FLAGS_PEDANTIC "-pedantic")

#Allow eclipse to discover include directories.
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Find dependencies.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
find_package (LibSndFile)

# Process CMakeLists files in these subdirectories.
add_subdirectory (include)
add_subdirectory (src)
