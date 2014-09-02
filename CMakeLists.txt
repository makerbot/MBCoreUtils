cmake_minimum_required(VERSION 2.6)
project(MBCoreUtils)
option(MBCOREUTILS_LIB_BUILD_SHARED
    "Build MBCOREUTILS_lib as a shared library."
    OFF)
if(MBCOREUTILS_LIB_BUILD_SHARED)
  set(MBCOREUTILS_LIB_TYPE SHARED)
  add_definitions( -DJSON_DLL_BUILD )
else()
  set(MBCOREUTILS_LIB_TYPE STATIC)
endif()

add_subdirectory(include/mbcoreutils)
