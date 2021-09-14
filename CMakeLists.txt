cmake_minimum_required(VERSION 3.0)
project(odourless)

if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
    message(FATAL_ERROR "Please set CMAKE_OSX_ARCHITECTURES (x86_64, arm64, arm64e)")
endif()

message("-- Arch: ${CMAKE_OSX_ARCHITECTURES}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)

set(wxBUILD_MONOLITHIC ON)
set(wxBUILD_SHARED OFF)
set(wxUSE_REGEX OFF)
set(wxUSE_LIBJPEG OFF)
#set(wxUSE_LIBPNG OFF)
set(wxUSE_LIBTIFF OFF)
set(wxBUILD_INSTALL OFF)
set(wxBUILD_SAMPLES OFF)
set(wxBUILD_TESTS OFF)
set(wxBUILD_DEMOS OFF)
set(wxBUILD_BENCHMARKS OFF)
set(wxBUILD_PRECOMP OFF)

add_subdirectory(vendor/wxWidgets)

set(ODOURLESS_VERSION 1.0.0)

set(ODOURLESS_MUST_INSTALL_TO_APPLICATIONS ON)

if (ODOURLESS_MUST_INSTALL_TO_APPLICATIONS)
    add_definitions(-DODOURLESS_MUST_INSTALL_TO_APPLICATIONS)
    add_definitions(-DODOURLESS_INSTALL_PATH="/Applications/Odourless.app")
else ()
    add_definitions(-DODOURLESS_INSTALL_PATH="${CMAKE_BINARY_DIR}/Odourless.app")
endif ()

add_definitions(-DODOURLESS_VERSION="${ODOURLESS_VERSION}")
add_definitions(-DCAGE_DIRECTORY_PATH="/usr/local/var/.odourless_cage")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Odourless.app/Contents/Resources/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Odourless.app/Contents/Resources/lib)

add_subdirectory(src/common)
add_subdirectory(src/inject-lib)
add_subdirectory(src/daemon)
add_subdirectory(src/ctl)
add_subdirectory(src/gui)

install(CODE "execute_process(COMMAND \"${CMAKE_SOURCE_DIR}/build-zip.sh\"
        \"${CMAKE_SOURCE_DIR}\"
        \"${CMAKE_BINARY_DIR}/Odourless.app\"
        \"${ODOURLESS_VERSION}\"
        \"${CMAKE_BINARY_DIR}/dist\"
        \"${CMAKE_OSX_ARCHITECTURES}\")")