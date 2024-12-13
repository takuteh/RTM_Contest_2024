# left_wheel CMake config file
#
# This file sets the following variables:
# left_wheel_FOUND - Always TRUE.
# left_wheel_INCLUDE_DIRS - Directories containing the left_wheel include files.
# left_wheel_IDL_DIRS - Directories containing the left_wheel IDL files.
# left_wheel_LIBRARIES - Libraries needed to use left_wheel.
# left_wheel_DEFINITIONS - Compiler flags for left_wheel.
# left_wheel_VERSION - The version of left_wheel found.
# left_wheel_VERSION_MAJOR - The major version of left_wheel found.
# left_wheel_VERSION_MINOR - The minor version of left_wheel found.
# left_wheel_VERSION_REVISION - The revision version of left_wheel found.
# left_wheel_VERSION_CANDIDATE - The candidate version of left_wheel found.

message(STATUS "Found left_wheel-")
set(left_wheel_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(left_wheel_INCLUDE_DIRS
#    "/usr/local/include/left_wheel-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(left_wheel_IDL_DIRS
#    "/usr/local/include/left_wheel-/idl")
set(left_wheel_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(left_wheel_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(left_wheel_LIBRARIES
        "/usr/local//libleft_wheel.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(left_wheel_LIBRARIES
        "/usr/local//libleft_wheel.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(left_wheel_DEFINITIONS ${<dependency>_DEFINITIONS})

set(left_wheel_VERSION )
set(left_wheel_VERSION_MAJOR )
set(left_wheel_VERSION_MINOR )
set(left_wheel_VERSION_REVISION )
set(left_wheel_VERSION_CANDIDATE )

