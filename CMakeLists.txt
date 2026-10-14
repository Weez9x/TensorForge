cmake_minimum_required(VERSION 3.20)
project(TensorForge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tensorforge
    src/main.cpp
    src/Matrix.cpp
)

target_include_directories(tensorforge PRIVATE include)

enable_testing()

add_executable(matrix_tests
    tests/MatrixTests.cpp
    src/Matrix.cpp
)

target_include_directories(matrix_tests PRIVATE include)

add_test(NAME matrix_tests COMMAND matrix_tests)

add_executable(matmul_benchmark
    benchmarks/MatMulBenchmark.cpp
    src/Matrix.cpp
)

target_include_directories(matmul_benchmark PRIVATE include)
