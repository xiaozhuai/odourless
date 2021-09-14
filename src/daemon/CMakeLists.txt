cmake_minimum_required(VERSION 3.0)
project(odourless-daemon)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ODOURLESS_DAEMON_SOURCE_FILES "./*.cpp" "./*.h")

set(CMAKE_EXE_LINKER_FLAGS "-s -Wl,-dead_strip ${CMAKE_EXE_LINKER_FLAGS}")

add_executable(odourless-daemon ${ODOURLESS_DAEMON_SOURCE_FILES})
target_include_directories(odourless-daemon PRIVATE ../common)
target_include_directories(odourless-daemon PRIVATE ../../vendor/frida-core/${CMAKE_OSX_ARCHITECTURES})
target_link_directories(odourless-daemon PRIVATE ../../vendor/frida-core/${CMAKE_OSX_ARCHITECTURES})
target_link_libraries(odourless-daemon odourless-common frida-core resolv bsm "-framework Foundation" "-framework AppKit")
