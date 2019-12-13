cmake_minimum_required(VERSION 3.0)
project(odourless-daemon)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ODOURLESS_DAEMON_SOURCE_FILES "./*.cpp" "./*.h")

add_executable(odourless-daemon ${ODOURLESS_DAEMON_SOURCE_FILES})
target_include_directories(odourless-daemon PRIVATE ../common)
target_include_directories(odourless-daemon PRIVATE ../../vendor/mach_inject)
target_link_libraries(odourless-daemon odourless-common mach_inject)
