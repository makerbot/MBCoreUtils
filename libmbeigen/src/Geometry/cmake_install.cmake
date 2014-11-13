# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry

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
   "/Eigen/src/Geometry/EulerAngles.h;/Eigen/src/Geometry/OrthoMethods.h;/Eigen/src/Geometry/RotationBase.h;/Eigen/src/Geometry/Transform.h;/Eigen/src/Geometry/AngleAxis.h;/Eigen/src/Geometry/ParametrizedLine.h;/Eigen/src/Geometry/Rotation2D.h;/Eigen/src/Geometry/Homogeneous.h;/Eigen/src/Geometry/Hyperplane.h;/Eigen/src/Geometry/AlignedBox.h;/Eigen/src/Geometry/Umeyama.h;/Eigen/src/Geometry/Scaling.h;/Eigen/src/Geometry/Quaternion.h;/Eigen/src/Geometry/Translation.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/Geometry" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/EulerAngles.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/OrthoMethods.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/RotationBase.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Transform.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/AngleAxis.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/ParametrizedLine.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Rotation2D.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Homogeneous.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Hyperplane.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/AlignedBox.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Umeyama.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Scaling.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Quaternion.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/Translation.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/arch/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

