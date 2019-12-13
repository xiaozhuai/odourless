cmake_minimum_required(VERSION 3.0)
project(bootstrap)

set(CMAKE_CXX_STANDARD 17)

# from osxinj https://github.com/scen/osxinj
add_library(bootstrap SHARED bootstrap.cpp)
target_compile_options(bootstrap PRIVATE "-w")
