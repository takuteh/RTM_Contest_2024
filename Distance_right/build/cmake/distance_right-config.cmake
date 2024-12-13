# Distance_right CMake config file
#
# This file sets the following variables:
# Distance_right_FOUND - Always TRUE.
# Distance_right_INCLUDE_DIRS - Directories containing the Distance_right include files.
# Distance_right_IDL_DIRS - Directories containing the Distance_right IDL files.
# Distance_right_LIBRARIES - Libraries needed to use Distance_right.
# Distance_right_DEFINITIONS - Compiler flags for Distance_right.
# Distance_right_VERSION - The version of Distance_right found.
# Distance_right_VERSION_MAJOR - The major version of Distance_right found.
# Distance_right_VERSION_MINOR - The minor version of Distance_right found.
# Distance_right_VERSION_REVISION - The revision version of Distance_right found.
# Distance_right_VERSION_CANDIDATE - The candidate version of Distance_right found.

message(STATUS "Found Distance_right-1.0.0")
set(Distance_right_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Distance_right_INCLUDE_DIRS
#    "/usr/local/include/distance_right-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Distance_right_IDL_DIRS
#    "/usr/local/include/distance_right-1/idl")
set(Distance_right_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Distance_right_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Distance_right_LIBRARIES
        "/usr/local//libdistance_right.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Distance_right_LIBRARIES
        "/usr/local//libdistance_right.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Distance_right_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Distance_right_VERSION 1.0.0)
set(Distance_right_VERSION_MAJOR 1)
set(Distance_right_VERSION_MINOR 0)
set(Distance_right_VERSION_REVISION 0)
set(Distance_right_VERSION_CANDIDATE )

