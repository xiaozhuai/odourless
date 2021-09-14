cmake_minimum_required(VERSION 3.0)
project(odourless-gui)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE ODOURLESS_GUI_SOURCE_FILES "./*.cpp" "./*.h")
file(GLOB_RECURSE ODOURLESS_GUI_RESOURCES "res/*")

add_executable(odourless MACOSX_BUNDLE ${ODOURLESS_GUI_SOURCE_FILES} ${ODOURLESS_GUI_RESOURCES})
target_include_directories(odourless PRIVATE ../common)
target_link_libraries(odourless odourless-common wxmono)

set_target_properties(odourless PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in"
        MACOSX_BUNDLE_BUNDLE_VERSION "${ODOURLESS_VERSION}"
        MACOSX_BUNDLE_LONG_VERSION_STRING "${ODOURLESS_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${ODOURLESS_VERSION}"
        RESOURCE "${ODOURLESS_GUI_RESOURCES}")

