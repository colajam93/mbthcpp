cmake_minimum_required(VERSION 3.10)
project(mbth)

set(CMAKE_CXX_STANDARD 17)


# library

set(header_files
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mbth/Iterators/Combinations.hpp)

add_library(mbth INTERFACE)
target_sources(mbth INTERFACE ${header_files})
target_include_directories(mbth INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)


# test

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/Catch2)
add_executable(runtest test/main.cpp)
target_link_libraries(runtest Catch2)
