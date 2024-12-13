# Forward_Module CMake config file
#
# This file sets the following variables:
# Forward_Module_FOUND - Always TRUE.
# Forward_Module_INCLUDE_DIRS - Directories containing the Forward_Module include files.
# Forward_Module_IDL_DIRS - Directories containing the Forward_Module IDL files.
# Forward_Module_LIBRARIES - Libraries needed to use Forward_Module.
# Forward_Module_DEFINITIONS - Compiler flags for Forward_Module.
# Forward_Module_VERSION - The version of Forward_Module found.
# Forward_Module_VERSION_MAJOR - The major version of Forward_Module found.
# Forward_Module_VERSION_MINOR - The minor version of Forward_Module found.
# Forward_Module_VERSION_REVISION - The revision version of Forward_Module found.
# Forward_Module_VERSION_CANDIDATE - The candidate version of Forward_Module found.

message(STATUS "Found Forward_Module-")
set(Forward_Module_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Forward_Module_INCLUDE_DIRS
#    "/usr/local/include/forward_module-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Forward_Module_IDL_DIRS
#    "/usr/local/include/forward_module-/idl")
set(Forward_Module_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Forward_Module_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Forward_Module_LIBRARIES
        "/usr/local//libforward_module.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Forward_Module_LIBRARIES
        "/usr/local//libforward_module.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Forward_Module_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Forward_Module_VERSION )
set(Forward_Module_VERSION_MAJOR )
set(Forward_Module_VERSION_MINOR )
set(Forward_Module_VERSION_REVISION )
set(Forward_Module_VERSION_CANDIDATE )

