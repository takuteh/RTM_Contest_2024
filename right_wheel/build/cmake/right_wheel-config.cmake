# right_wheel CMake config file
#
# This file sets the following variables:
# right_wheel_FOUND - Always TRUE.
# right_wheel_INCLUDE_DIRS - Directories containing the right_wheel include files.
# right_wheel_IDL_DIRS - Directories containing the right_wheel IDL files.
# right_wheel_LIBRARIES - Libraries needed to use right_wheel.
# right_wheel_DEFINITIONS - Compiler flags for right_wheel.
# right_wheel_VERSION - The version of right_wheel found.
# right_wheel_VERSION_MAJOR - The major version of right_wheel found.
# right_wheel_VERSION_MINOR - The minor version of right_wheel found.
# right_wheel_VERSION_REVISION - The revision version of right_wheel found.
# right_wheel_VERSION_CANDIDATE - The candidate version of right_wheel found.

message(STATUS "Found right_wheel-")
set(right_wheel_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(right_wheel_INCLUDE_DIRS
#    "/usr/local/include/right_wheel-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(right_wheel_IDL_DIRS
#    "/usr/local/include/right_wheel-/idl")
set(right_wheel_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(right_wheel_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(right_wheel_LIBRARIES
        "/usr/local//libright_wheel.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(right_wheel_LIBRARIES
        "/usr/local//libright_wheel.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(right_wheel_DEFINITIONS ${<dependency>_DEFINITIONS})

set(right_wheel_VERSION )
set(right_wheel_VERSION_MAJOR )
set(right_wheel_VERSION_MINOR )
set(right_wheel_VERSION_REVISION )
set(right_wheel_VERSION_CANDIDATE )

