cmake_minimum_required(VERSION 3.16.3)

project(dfmlTest DESCRIPTION "dfml testing" LANGUAGES CXX)

set(EXECUTABLE test)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)
#pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
#pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
#pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_executable(${EXECUTABLE} ${SOURCES})

target_include_directories(${EXECUTABLE} PUBLIC ${INC_DIR})
target_include_directories(${EXECUTABLE} PUBLIC ${PROJECT_SOURCE_DIR}/../../doctest/doctest)

#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
#include_directories(${SDL2_MIXER_INCLUDE_DIRS})
#include_directories(${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} dfml)
