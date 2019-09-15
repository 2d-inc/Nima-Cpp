cmake_minimum_required(VERSION 3.14)
project(nima)

set(CMAKE_CXX_STANDARD 11)

option(NIMA_OPTION_BUILD_STATIC "Build static library, otherwise build shared" ON)

file(GLOB_RECURSE ALL_NIMA_SRC "Source/*.cpp")
file(GLOB_RECURSE ALL_NIMA_MATH_SRC "Nima-Math-Cpp/Source/*.cpp")

include_directories(nima Source Nima-Math-Cpp/Source)

if(NIMA_OPTION_BUILD_STATIC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_library(nima ${LIB_TYPE} ${ALL_NIMA_SRC} ${ALL_NIMA_MATH_SRC})
target_include_directories(nima PUBLIC Source Nima-Math-Cpp/Source)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(nima PRIVATE -Wall -Werror -g -std=c++11)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(nima PRIVATE /WX /W3 /std:c++14)
    target_compile_definitions(nima PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()