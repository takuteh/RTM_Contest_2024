# Turning_Module CMake config file
#
# This file sets the following variables:
# Turning_Module_FOUND - Always TRUE.
# Turning_Module_INCLUDE_DIRS - Directories containing the Turning_Module include files.
# Turning_Module_IDL_DIRS - Directories containing the Turning_Module IDL files.
# Turning_Module_LIBRARIES - Libraries needed to use Turning_Module.
# Turning_Module_DEFINITIONS - Compiler flags for Turning_Module.
# Turning_Module_VERSION - The version of Turning_Module found.
# Turning_Module_VERSION_MAJOR - The major version of Turning_Module found.
# Turning_Module_VERSION_MINOR - The minor version of Turning_Module found.
# Turning_Module_VERSION_REVISION - The revision version of Turning_Module found.
# Turning_Module_VERSION_CANDIDATE - The candidate version of Turning_Module found.

message(STATUS "Found Turning_Module-")
set(Turning_Module_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Turning_Module_INCLUDE_DIRS
#    "/usr/local/include/turning_module-"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Turning_Module_IDL_DIRS
#    "/usr/local/include/turning_module-/idl")
set(Turning_Module_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Turning_Module_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Turning_Module_LIBRARIES
        "/usr/local//libturning_module.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Turning_Module_LIBRARIES
        "/usr/local//libturning_module.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Turning_Module_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Turning_Module_VERSION )
set(Turning_Module_VERSION_MAJOR )
set(Turning_Module_VERSION_MINOR )
set(Turning_Module_VERSION_REVISION )
set(Turning_Module_VERSION_CANDIDATE )

