cmake_minimum_required(VERSION 3.10)

project(stack-lang)

set(CMAKE_CXX_COMPILER g++) 

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++2a")
SET(GCC_COVERAGE_LINK_FLAGS    "")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(stack-lang 
	src/main.cpp
	src/err.cpp
	src/parser.cpp
	src/eval.cpp
	src/generator.cpp
	src/test.cpp)

target_include_directories(stack-lang PUBLIC 
	include)
