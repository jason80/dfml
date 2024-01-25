cmake_minimum_required(VERSION 3.16.3)

project(dfml_global LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(main)
add_subdirectory(test)
