# Jump_Module CMake config file
#
# This file sets the following variables:
# Jump_Module_FOUND - Always TRUE.
# Jump_Module_INCLUDE_DIRS - Directories containing the Jump_Module include files.
# Jump_Module_IDL_DIRS - Directories containing the Jump_Module IDL files.
# Jump_Module_LIBRARIES - Libraries needed to use Jump_Module.
# Jump_Module_DEFINITIONS - Compiler flags for Jump_Module.
# Jump_Module_VERSION - The version of Jump_Module found.
# Jump_Module_VERSION_MAJOR - The major version of Jump_Module found.
# Jump_Module_VERSION_MINOR - The minor version of Jump_Module found.
# Jump_Module_VERSION_REVISION - The revision version of Jump_Module found.
# Jump_Module_VERSION_CANDIDATE - The candidate version of Jump_Module found.

message(STATUS "Found Jump_Module-")
set(Jump_Module_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Jump_Module_INCLUDE_DIRS
#    "/usr/local/include/jump_module-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Jump_Module_IDL_DIRS
#    "/usr/local/include/jump_module-/idl")
set(Jump_Module_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Jump_Module_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Jump_Module_LIBRARIES
        "/usr/local//libjump_module.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Jump_Module_LIBRARIES
        "/usr/local//libjump_module.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Jump_Module_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Jump_Module_VERSION )
set(Jump_Module_VERSION_MAJOR )
set(Jump_Module_VERSION_MINOR )
set(Jump_Module_VERSION_REVISION )
set(Jump_Module_VERSION_CANDIDATE )

