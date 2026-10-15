cmake_minimum_required(VERSION 3.16)
project(lab_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(polynomial_lib STATIC src/polynomial.cpp)
target_include_directories(polynomial_lib PUBLIC src)

add_executable(lab02_app main.cpp)
target_link_libraries(lab02_app PRIVATE polynomial_lib)

add_executable(lab02_tests tests/tests_poly.cpp)
target_link_libraries(lab02_tests
    PRIVATE
        polynomial_lib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab02_tests)