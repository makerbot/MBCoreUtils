# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Eigen/src/Core/util/Memory.h;/Eigen/src/Core/util/XprHelper.h;/Eigen/src/Core/util/NonMPL2.h;/Eigen/src/Core/util/ReenableStupidWarnings.h;/Eigen/src/Core/util/Macros.h;/Eigen/src/Core/util/Meta.h;/Eigen/src/Core/util/MKL_support.h;/Eigen/src/Core/util/Constants.h;/Eigen/src/Core/util/DisableStupidWarnings.h;/Eigen/src/Core/util/BlasUtil.h;/Eigen/src/Core/util/StaticAssert.h;/Eigen/src/Core/util/ForwardDeclarations.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/Core/util" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/Memory.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/XprHelper.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/NonMPL2.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/ReenableStupidWarnings.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/Macros.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/Meta.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/MKL_support.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/Constants.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/DisableStupidWarnings.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/BlasUtil.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/StaticAssert.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/util/ForwardDeclarations.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

