cmake_minimum_required(VERSION 3.0)
project(odourless-inject)

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE ODOURLESS_INJECT_SOURCE_FILES "./*.cpp" "./*.h")

add_library(odourless-inject SHARED ${ODOURLESS_INJECT_SOURCE_FILES})
target_include_directories(odourless-inject PRIVATE ../common)
target_include_directories(odourless-inject PRIVATE ../../vendor/frida-gum)
target_link_directories(odourless-inject PRIVATE ../../vendor/frida-gum)
target_link_libraries(odourless-inject odourless-common frida-gum resolv)
