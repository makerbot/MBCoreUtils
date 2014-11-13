# Install script for directory: /home/ryan/Toolchain-Release/Toolchain/libmbeigen/src

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

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Householder/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/UmfPackSupport/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCore/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/PaStiXSupport/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SVD/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/PardisoSupport/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/misc/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Geometry/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Cholesky/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigenvalues/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/LU/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Eigen2Support/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SuperLUSupport/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/OrderingMethods/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/IterativeLinearSolvers/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/QR/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/StlSupport/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Jacobi/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/plugins/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/SparseCholesky/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/Core/cmake_install.cmake")
  INCLUDE("/home/ryan/Toolchain-Release/Toolchain/libmbeigen/src/CholmodSupport/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

