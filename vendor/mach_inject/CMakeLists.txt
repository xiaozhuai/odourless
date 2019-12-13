cmake_minimum_required(VERSION 3.0)
project(mach_inject)

set(CMAKE_CXX_STANDARD 17)

# form mach_inject https://github.com/rentzsch/mach_inject
add_library(mach_inject STATIC mach_inject.h mach_inject.c)
target_compile_options(mach_inject PRIVATE "-w")

