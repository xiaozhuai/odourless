cmake_minimum_required(VERSION 3.0)
project(odourless-common)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ODOURLESS_COMMON_SOURCE_FILES "./*.cpp" "./*.h")

add_library(odourless-common STATIC ${ODOURLESS_COMMON_SOURCE_FILES})
