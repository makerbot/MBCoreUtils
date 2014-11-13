# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support

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
   "/Eigen/src/Eigen2Support/MathFunctions.h;/Eigen/src/Eigen2Support/Memory.h;/Eigen/src/Eigen2Support/Block.h;/Eigen/src/Eigen2Support/LU.h;/Eigen/src/Eigen2Support/Cwise.h;/Eigen/src/Eigen2Support/Macros.h;/Eigen/src/Eigen2Support/SVD.h;/Eigen/src/Eigen2Support/Meta.h;/Eigen/src/Eigen2Support/TriangularSolver.h;/Eigen/src/Eigen2Support/Minor.h;/Eigen/src/Eigen2Support/CwiseOperators.h;/Eigen/src/Eigen2Support/VectorBlock.h;/Eigen/src/Eigen2Support/Lazy.h;/Eigen/src/Eigen2Support/QR.h;/Eigen/src/Eigen2Support/LeastSquares.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/Eigen2Support" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/MathFunctions.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Memory.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Block.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/LU.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Cwise.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Macros.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/SVD.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Meta.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/TriangularSolver.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Minor.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/CwiseOperators.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/VectorBlock.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Lazy.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/QR.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/LeastSquares.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/Geometry/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

