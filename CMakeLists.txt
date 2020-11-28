cmake_minimum_required(VERSION 3.16)
project(libcpparg)

set(CMAKE_CXX_STANDARD 20)

add_library(libcpparg_shared SHARED libcpparg/parser.cpp libcpparg/parser.h libcpparg/utils.h libcpparg/parsed_arg.cpp)
add_library(libcpparg_static STATIC libcpparg/parser.cpp libcpparg/parser.h libcpparg/utils.h libcpparg/parsed_arg.cpp)

target_compile_definitions(libcpparg_shared PUBLIC BUILDING_DLL)