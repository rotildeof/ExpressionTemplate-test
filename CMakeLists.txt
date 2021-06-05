cmake_minimum_required(VERSION 3.14)
project(expression_template CXX)
set(CMAKE_CXX_STANDARD 14)

add_compile_options(-O2 -Wall)

add_executable(test.exe test.cxx)