# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Eigen/src/Eigen2Support/Geometry/All.h;/Eigen/src/Eigen2Support/Geometry/RotationBase.h;/Eigen/src/Eigen2Support/Geometry/Transform.h;/Eigen/src/Eigen2Support/Geometry/AngleAxis.h;/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h;/Eigen/src/Eigen2Support/Geometry/Rotation2D.h;/Eigen/src/Eigen2Support/Geometry/Hyperplane.h;/Eigen/src/Eigen2Support/Geometry/AlignedBox.h;/Eigen/src/Eigen2Support/Geometry/Scaling.h;/Eigen/src/Eigen2Support/Geometry/Quaternion.h;/Eigen/src/Eigen2Support/Geometry/Translation.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/Eigen2Support/Geometry" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/All.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/RotationBase.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Transform.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/AngleAxis.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/ParametrizedLine.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Rotation2D.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Hyperplane.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/AlignedBox.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Scaling.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Quaternion.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/Translation.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

