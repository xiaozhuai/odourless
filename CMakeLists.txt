cmake_minimum_required(VERSION 3.0)
project(odourless)

set(CMAKE_CXX_STANDARD 11)

set(ODOURLESS_VERSION 0.0.3)

set(ODOURLESS_MUST_INSTALL_TO_APPLICATIONS ON)

if(ODOURLESS_MUST_INSTALL_TO_APPLICATIONS)
    add_definitions(-DODOURLESS_MUST_INSTALL_TO_APPLICATIONS)
    add_definitions(-DODOURLESS_INSTALL_PATH="/Applications/Odourless.app")
else()
    add_definitions(-DODOURLESS_INSTALL_PATH="${CMAKE_BINARY_DIR}/Odourless.app")
endif()

add_definitions(-DODOURLESS_VERSION="${ODOURLESS_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Odourless.app/Contents/Resources/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Odourless.app/Contents/Resources/lib)

add_subdirectory(src/common)
add_subdirectory(src/inject-lib)
add_subdirectory(src/daemon)
add_subdirectory(src/ctl)
add_subdirectory(src/gui)
add_subdirectory(vendor/mach_inject)
add_subdirectory(vendor/osxinj)

install(CODE "execute_process(COMMAND \"${CMAKE_SOURCE_DIR}/build-zip.sh\"
        \"${CMAKE_SOURCE_DIR}\"
        \"${CMAKE_BINARY_DIR}/Odourless.app\"
        \"${ODOURLESS_VERSION}\"
        \"${CMAKE_BINARY_DIR}/dist\")")