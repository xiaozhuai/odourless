cmake_minimum_required(VERSION 3.0)
project(odourless-ctl)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ODOURLESS_CTL_SOURCE_FILES "./*.cpp" "./*.h")

add_executable(odourless-ctl ${ODOURLESS_CTL_SOURCE_FILES})
target_include_directories(odourless-ctl PRIVATE ../common)
target_link_libraries(odourless-ctl odourless-common)
