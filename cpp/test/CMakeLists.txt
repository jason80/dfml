cmake_minimum_required(VERSION 3.16.3)

project(dfmlTest DESCRIPTION "dfml testing" LANGUAGES CXX)

set(EXECUTABLE test)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_executable(${EXECUTABLE} ${SOURCES})

target_include_directories(${EXECUTABLE} PUBLIC ${INC_DIR})
target_include_directories(${EXECUTABLE} PUBLIC ${PROJECT_SOURCE_DIR}/../../doctest/doctest)

target_link_libraries(${EXECUTABLE} dfml)
