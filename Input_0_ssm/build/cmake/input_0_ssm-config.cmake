# Input_0_ssm CMake config file
#
# This file sets the following variables:
# Input_0_ssm_FOUND - Always TRUE.
# Input_0_ssm_INCLUDE_DIRS - Directories containing the Input_0_ssm include files.
# Input_0_ssm_IDL_DIRS - Directories containing the Input_0_ssm IDL files.
# Input_0_ssm_LIBRARIES - Libraries needed to use Input_0_ssm.
# Input_0_ssm_DEFINITIONS - Compiler flags for Input_0_ssm.
# Input_0_ssm_VERSION - The version of Input_0_ssm found.
# Input_0_ssm_VERSION_MAJOR - The major version of Input_0_ssm found.
# Input_0_ssm_VERSION_MINOR - The minor version of Input_0_ssm found.
# Input_0_ssm_VERSION_REVISION - The revision version of Input_0_ssm found.
# Input_0_ssm_VERSION_CANDIDATE - The candidate version of Input_0_ssm found.

message(STATUS "Found Input_0_ssm-")
set(Input_0_ssm_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Input_0_ssm_INCLUDE_DIRS
#    "/usr/local/include/input_0_ssm-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Input_0_ssm_IDL_DIRS
#    "/usr/local/include/input_0_ssm-/idl")
set(Input_0_ssm_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Input_0_ssm_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Input_0_ssm_LIBRARIES
        "/usr/local//libinput_0_ssm.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Input_0_ssm_LIBRARIES
        "/usr/local//libinput_0_ssm.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Input_0_ssm_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Input_0_ssm_VERSION )
set(Input_0_ssm_VERSION_MAJOR )
set(Input_0_ssm_VERSION_MINOR )
set(Input_0_ssm_VERSION_REVISION )
set(Input_0_ssm_VERSION_CANDIDATE )

