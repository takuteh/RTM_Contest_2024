# Distance_left CMake config file
#
# This file sets the following variables:
# Distance_left_FOUND - Always TRUE.
# Distance_left_INCLUDE_DIRS - Directories containing the Distance_left include files.
# Distance_left_IDL_DIRS - Directories containing the Distance_left IDL files.
# Distance_left_LIBRARIES - Libraries needed to use Distance_left.
# Distance_left_DEFINITIONS - Compiler flags for Distance_left.
# Distance_left_VERSION - The version of Distance_left found.
# Distance_left_VERSION_MAJOR - The major version of Distance_left found.
# Distance_left_VERSION_MINOR - The minor version of Distance_left found.
# Distance_left_VERSION_REVISION - The revision version of Distance_left found.
# Distance_left_VERSION_CANDIDATE - The candidate version of Distance_left found.

message(STATUS "Found Distance_left-1.0.0")
set(Distance_left_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Distance_left_INCLUDE_DIRS
#    "/usr/local/include/distance_left-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Distance_left_IDL_DIRS
#    "/usr/local/include/distance_left-1/idl")
set(Distance_left_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Distance_left_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Distance_left_LIBRARIES
        "/usr/local//libdistance_left.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Distance_left_LIBRARIES
        "/usr/local//libdistance_left.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Distance_left_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Distance_left_VERSION 1.0.0)
set(Distance_left_VERSION_MAJOR 1)
set(Distance_left_VERSION_MINOR 0)
set(Distance_left_VERSION_REVISION 0)
set(Distance_left_VERSION_CANDIDATE )

