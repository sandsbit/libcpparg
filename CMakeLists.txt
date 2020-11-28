cmake_minimum_required(VERSION 3.16)
project(libcpparg)

set(CMAKE_CXX_STANDARD 20)

add_library(libcpparg_shared SHARED libcpparg/parsing/parser.cpp libcpparg/parsing/parser.h libcpparg/misc/utils.h libcpparg/parsing/parsed_arg.cpp libcpparg/parsing/parsing_util_classes.h)
add_library(libcpparg_static STATIC libcpparg/parsing/parser.cpp libcpparg/parsing/parser.h libcpparg/misc/utils.h libcpparg/parsing/parsed_arg.cpp)

target_compile_definitions(libcpparg_shared PUBLIC BUILDING_DLL)