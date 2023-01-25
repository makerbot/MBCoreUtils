cmake_minimum_required(VERSION 3.19.0)
project(MBCoreUtils)

find_package(jsoncpp REQUIRED)

add_library(MBCoreUtils INTERFACE)
target_include_directories(MBCoreUtils INTERFACE include)
target_link_libraries(MBCoreUtils INTERFACE jsoncpp::jsoncpp)