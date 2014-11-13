# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues

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
   "/Eigen/src/Eigenvalues/RealSchur_MKL.h;/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h;/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h;/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h;/Eigen/src/Eigenvalues/ComplexEigenSolver.h;/Eigen/src/Eigenvalues/HessenbergDecomposition.h;/Eigen/src/Eigenvalues/ComplexSchur_MKL.h;/Eigen/src/Eigenvalues/Tridiagonalization.h;/Eigen/src/Eigenvalues/EigenSolver.h;/Eigen/src/Eigenvalues/ComplexSchur.h;/Eigen/src/Eigenvalues/RealSchur.h;/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/Eigenvalues" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/RealSchur_MKL.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/SelfAdjointEigenSolver.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/MatrixBaseEigenvalues.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/ComplexEigenSolver.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/HessenbergDecomposition.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/ComplexSchur_MKL.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/Tridiagonalization.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/EigenSolver.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/ComplexSchur.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/RealSchur.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

