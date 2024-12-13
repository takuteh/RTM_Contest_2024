# reel_ssm CMake config file
#
# This file sets the following variables:
# reel_ssm_FOUND - Always TRUE.
# reel_ssm_INCLUDE_DIRS - Directories containing the reel_ssm include files.
# reel_ssm_IDL_DIRS - Directories containing the reel_ssm IDL files.
# reel_ssm_LIBRARIES - Libraries needed to use reel_ssm.
# reel_ssm_DEFINITIONS - Compiler flags for reel_ssm.
# reel_ssm_VERSION - The version of reel_ssm found.
# reel_ssm_VERSION_MAJOR - The major version of reel_ssm found.
# reel_ssm_VERSION_MINOR - The minor version of reel_ssm found.
# reel_ssm_VERSION_REVISION - The revision version of reel_ssm found.
# reel_ssm_VERSION_CANDIDATE - The candidate version of reel_ssm found.

message(STATUS "Found reel_ssm-")
set(reel_ssm_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(reel_ssm_INCLUDE_DIRS
#    "/usr/local/include/reel_ssm-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(reel_ssm_IDL_DIRS
#    "/usr/local/include/reel_ssm-/idl")
set(reel_ssm_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(reel_ssm_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(reel_ssm_LIBRARIES
        "/usr/local//libreel_ssm.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(reel_ssm_LIBRARIES
        "/usr/local//libreel_ssm.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(reel_ssm_DEFINITIONS ${<dependency>_DEFINITIONS})

set(reel_ssm_VERSION )
set(reel_ssm_VERSION_MAJOR )
set(reel_ssm_VERSION_MINOR )
set(reel_ssm_VERSION_REVISION )
set(reel_ssm_VERSION_CANDIDATE )

