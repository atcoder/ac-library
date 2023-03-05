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

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(.)
include_directories(../../)

add_executable(BasicTest basic_test.cpp)
target_link_libraries(BasicTest gtest gtest_main)
gtest_discover_tests(BasicTest)

add_executable(SegtreeTest segtree_test.cpp)
target_link_libraries(SegtreeTest gtest gtest_main)
gtest_discover_tests(SegtreeTest)

add_executable(LazySegtreeTest lazysegtree_test.cpp)
target_link_libraries(LazySegtreeTest gtest gtest_main)
gtest_discover_tests(LazySegtreeTest)

add_executable(LazySegtreeStressTest lazysegtree_stress_test.cpp)
target_link_libraries(LazySegtreeStressTest gtest gtest_main)
gtest_discover_tests(LazySegtreeStressTest)

add_executable(MathTest math_test.cpp)
target_link_libraries(MathTest gtest gtest_main)
gtest_discover_tests(MathTest)

add_executable(InternalMathTest internal_math_test.cpp)
target_link_libraries(InternalMathTest gtest gtest_main)
gtest_discover_tests(InternalMathTest)

add_executable(ModintTest modint_test.cpp)
target_link_libraries(ModintTest gtest gtest_main)
gtest_discover_tests(ModintTest)

add_executable(DSUTest dsu_test.cpp)
target_link_libraries(DSUTest gtest gtest_main)
gtest_discover_tests(DSUTest)

add_executable(FenwickTreeTest fenwicktree_test.cpp)
target_link_libraries(FenwickTreeTest gtest gtest_main)
gtest_discover_tests(FenwickTreeTest)

add_executable(SCCTest scc_test.cpp)
target_link_libraries(SCCTest gtest gtest_main)
gtest_discover_tests(SCCTest)

add_executable(TwosatTest twosat_test.cpp)
target_link_libraries(TwosatTest gtest gtest_main)
gtest_discover_tests(TwosatTest)

add_executable(StringTest string_test.cpp)
target_link_libraries(StringTest gtest gtest_main)
gtest_discover_tests(StringTest)

add_executable(ConvolutionTest convolution_test.cpp)
target_link_libraries(ConvolutionTest gtest gtest_main)
gtest_discover_tests(ConvolutionTest)

add_executable(MaxflowTest maxflow_test.cpp)
target_link_libraries(MaxflowTest gtest gtest_main)
gtest_discover_tests(MaxflowTest)

add_executable(MincostflowTest mincostflow_test.cpp)
target_link_libraries(MincostflowTest gtest gtest_main)
gtest_discover_tests(MincostflowTest)

add_executable(BitTest bit_test.cpp)
target_link_libraries(BitTest gtest gtest_main)
gtest_discover_tests(BitTest)

add_executable(TypeTraitsTest type_traits_test.cpp)
target_link_libraries(TypeTraitsTest gtest gtest_main)
gtest_discover_tests(TypeTraitsTest)

# utils
add_executable(UtilsMathTest utils/math_test.cpp)
target_link_libraries(UtilsMathTest gtest gtest_main)
gtest_discover_tests(UtilsMathTest)
