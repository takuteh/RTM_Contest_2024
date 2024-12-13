# Install script for directory: /home/takumi/RTComponent/ssm_comp/Input_0_ssm/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcomponentx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm" TYPE SHARED_LIBRARY FILES "/home/takumi/RTComponent/ssm_comp/Input_0_ssm/build/src/Input_0_ssm.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssm.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcomponentx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcomponentx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm" TYPE EXECUTABLE FILES "/home/takumi/RTComponent/ssm_comp/Input_0_ssm/build/src/Input_0_ssmComp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm/Input_0_ssmComp")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xcomponentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openrtm-2.0/components/c++/Category/Input_0_ssm" TYPE FILE FILES "/home/takumi/RTComponent/ssm_comp/Input_0_ssm/RTC.xml")
endif()

