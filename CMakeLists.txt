cmake_minimum_required(VERSION 3.10)
project(mbth)

set(CMAKE_CXX_STANDARD 17)


# library

set(header_files)

add_library(mbth INTERFACE)
target_sources(mbth INTERFACE ${header_files})
target_include_directories(mbth INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)


# test

add_executable(runtest test/main.cpp)
