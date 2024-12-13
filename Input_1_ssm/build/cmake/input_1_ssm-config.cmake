# Input_1_ssm CMake config file
#
# This file sets the following variables:
# Input_1_ssm_FOUND - Always TRUE.
# Input_1_ssm_INCLUDE_DIRS - Directories containing the Input_1_ssm include files.
# Input_1_ssm_IDL_DIRS - Directories containing the Input_1_ssm IDL files.
# Input_1_ssm_LIBRARIES - Libraries needed to use Input_1_ssm.
# Input_1_ssm_DEFINITIONS - Compiler flags for Input_1_ssm.
# Input_1_ssm_VERSION - The version of Input_1_ssm found.
# Input_1_ssm_VERSION_MAJOR - The major version of Input_1_ssm found.
# Input_1_ssm_VERSION_MINOR - The minor version of Input_1_ssm found.
# Input_1_ssm_VERSION_REVISION - The revision version of Input_1_ssm found.
# Input_1_ssm_VERSION_CANDIDATE - The candidate version of Input_1_ssm found.

message(STATUS "Found Input_1_ssm-1.0.0")
set(Input_1_ssm_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Input_1_ssm_INCLUDE_DIRS
#    "/usr/local/include/input_1_ssm-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Input_1_ssm_IDL_DIRS
#    "/usr/local/include/input_1_ssm-1/idl")
set(Input_1_ssm_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Input_1_ssm_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Input_1_ssm_LIBRARIES
        "/usr/local//libinput_1_ssm.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Input_1_ssm_LIBRARIES
        "/usr/local//libinput_1_ssm.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Input_1_ssm_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Input_1_ssm_VERSION 1.0.0)
set(Input_1_ssm_VERSION_MAJOR 1)
set(Input_1_ssm_VERSION_MINOR 0)
set(Input_1_ssm_VERSION_REVISION 0)
set(Input_1_ssm_VERSION_CANDIDATE )

