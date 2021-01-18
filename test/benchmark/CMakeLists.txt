cmake_policy(SET CMP0048 NEW)
project(ACLibrary)

cmake_minimum_required(VERSION 3.17)

set(GOOGLETEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../unittest/googletest")

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Werror)

add_subdirectory(benchmark)

include_directories(.)
include_directories(../../)

add_executable(Convolution convolution.cpp)
target_link_libraries(Convolution benchmark::benchmark)
