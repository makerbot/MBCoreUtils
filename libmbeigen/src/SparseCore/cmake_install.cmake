# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore

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
   "/Eigen/src/SparseCore/SparseMatrix.h;/Eigen/src/SparseCore/SparseTriangularView.h;/Eigen/src/SparseCore/SparseAssign.h;/Eigen/src/SparseCore/SparseFuzzy.h;/Eigen/src/SparseCore/SparseTranspose.h;/Eigen/src/SparseCore/SparseMatrixBase.h;/Eigen/src/SparseCore/CoreIterators.h;/Eigen/src/SparseCore/SparseDenseProduct.h;/Eigen/src/SparseCore/TriangularSolver.h;/Eigen/src/SparseCore/SparseSelfAdjointView.h;/Eigen/src/SparseCore/CompressedStorage.h;/Eigen/src/SparseCore/SparseRedux.h;/Eigen/src/SparseCore/SparseCwiseUnaryOp.h;/Eigen/src/SparseCore/SparseBlock.h;/Eigen/src/SparseCore/SparseProduct.h;/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h;/Eigen/src/SparseCore/SparseSparseProductWithPruning.h;/Eigen/src/SparseCore/SparseView.h;/Eigen/src/SparseCore/SparseUtil.h;/Eigen/src/SparseCore/MappedSparseMatrix.h;/Eigen/src/SparseCore/SparseVector.h;/Eigen/src/SparseCore/SparsePermutation.h;/Eigen/src/SparseCore/SparseDot.h;/Eigen/src/SparseCore/AmbiVector.h;/Eigen/src/SparseCore/SparseCwiseBinaryOp.h;/Eigen/src/SparseCore/SparseDiagonalProduct.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/Eigen/src/SparseCore" TYPE FILE FILES
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseMatrix.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseTriangularView.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseAssign.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseFuzzy.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseTranspose.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseMatrixBase.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/CoreIterators.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseDenseProduct.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/TriangularSolver.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseSelfAdjointView.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/CompressedStorage.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseRedux.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseCwiseUnaryOp.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseBlock.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseProduct.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/ConservativeSparseSparseProduct.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseSparseProductWithPruning.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseView.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseUtil.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/MappedSparseMatrix.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseVector.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparsePermutation.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseDot.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/AmbiVector.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseCwiseBinaryOp.h"
    "/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/SparseDiagonalProduct.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

