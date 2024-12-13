# Avoid_Module CMake config file
#
# This file sets the following variables:
# Avoid_Module_FOUND - Always TRUE.
# Avoid_Module_INCLUDE_DIRS - Directories containing the Avoid_Module include files.
# Avoid_Module_IDL_DIRS - Directories containing the Avoid_Module IDL files.
# Avoid_Module_LIBRARIES - Libraries needed to use Avoid_Module.
# Avoid_Module_DEFINITIONS - Compiler flags for Avoid_Module.
# Avoid_Module_VERSION - The version of Avoid_Module found.
# Avoid_Module_VERSION_MAJOR - The major version of Avoid_Module found.
# Avoid_Module_VERSION_MINOR - The minor version of Avoid_Module found.
# Avoid_Module_VERSION_REVISION - The revision version of Avoid_Module found.
# Avoid_Module_VERSION_CANDIDATE - The candidate version of Avoid_Module found.

message(STATUS "Found Avoid_Module-1.0.0")
set(Avoid_Module_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Avoid_Module_INCLUDE_DIRS
#    "/usr/local/include/avoid_module-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Avoid_Module_IDL_DIRS
#    "/usr/local/include/avoid_module-1/idl")
set(Avoid_Module_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Avoid_Module_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Avoid_Module_LIBRARIES
        "/usr/local//libavoid_module.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Avoid_Module_LIBRARIES
        "/usr/local//libavoid_module.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Avoid_Module_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Avoid_Module_VERSION 1.0.0)
set(Avoid_Module_VERSION_MAJOR 1)
set(Avoid_Module_VERSION_MINOR 0)
set(Avoid_Module_VERSION_REVISION 0)
set(Avoid_Module_VERSION_CANDIDATE )

