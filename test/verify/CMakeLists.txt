cmake_policy(SET CMP0048 NEW)
project(ACLibrary)

cmake_minimum_required(VERSION 3.17)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    message("Not MSVC")
    add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Werror)
    add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)
    add_link_options(-fsanitize=undefined,address)
else()
    message("Use MSVC")
    add_compile_options(/W4 /permissive- /sdl)
endif()

enable_testing()

include_directories(.)
include_directories(../../)

add_executable(FormalPowerSeriesTest
        fps_exp.test.cpp
        fps_inv.test.cpp
        fps_log.test.cpp
        fps_pow.test.cpp
        )
