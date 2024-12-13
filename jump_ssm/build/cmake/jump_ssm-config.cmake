# jump_ssm CMake config file
#
# This file sets the following variables:
# jump_ssm_FOUND - Always TRUE.
# jump_ssm_INCLUDE_DIRS - Directories containing the jump_ssm include files.
# jump_ssm_IDL_DIRS - Directories containing the jump_ssm IDL files.
# jump_ssm_LIBRARIES - Libraries needed to use jump_ssm.
# jump_ssm_DEFINITIONS - Compiler flags for jump_ssm.
# jump_ssm_VERSION - The version of jump_ssm found.
# jump_ssm_VERSION_MAJOR - The major version of jump_ssm found.
# jump_ssm_VERSION_MINOR - The minor version of jump_ssm found.
# jump_ssm_VERSION_REVISION - The revision version of jump_ssm found.
# jump_ssm_VERSION_CANDIDATE - The candidate version of jump_ssm found.

message(STATUS "Found jump_ssm-")
set(jump_ssm_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(jump_ssm_INCLUDE_DIRS
#    "/usr/local/include/jump_ssm-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(jump_ssm_IDL_DIRS
#    "/usr/local/include/jump_ssm-/idl")
set(jump_ssm_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(jump_ssm_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(jump_ssm_LIBRARIES
        "/usr/local//libjump_ssm.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(jump_ssm_LIBRARIES
        "/usr/local//libjump_ssm.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(jump_ssm_DEFINITIONS ${<dependency>_DEFINITIONS})

set(jump_ssm_VERSION )
set(jump_ssm_VERSION_MAJOR )
set(jump_ssm_VERSION_MINOR )
set(jump_ssm_VERSION_REVISION )
set(jump_ssm_VERSION_CANDIDATE )

