#include "Matrix.h"
#include <chrono>
#include <cstddef>
#include <iostream>

void RunBanchmark(std::size_t n)
{
    std::cout << "Test IJK" << std::endl;
    Matrix a(n, n);
    Matrix b(n, n);

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            a(i, j) = 1.0f;
        }
    }

    for (std::size_t i = 0; i < b.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            b(i, j) = 1.0f;
        }
    }

    {
        Matrix c = MatMultipli(a, b);
        std::cout << "test value c(0,0): " << c(0, 0) << std::endl;
    }
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMultipli(a, b);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        resultTime += elapsedMs;
        std::cout << "Attempt " << (i + 1) << ": " << elapsedMs << " ms"
                  << ", result(0, 0): " << result(0, 0) << '\n';
    }
    // std::cout << "Time: " << elapsedMs << " ms\n";
    // std::cout << "Result(0, 0): " << result(0, 0) << '\n';
    std::cout << "Matrix size: " << n << std::endl;
    std::cout << "Average time: " << (resultTime / 5.0) << " ms" << std::endl;
}

void RunBanchmarkIKJ(std::size_t n)
{
    std::cout << "Test IKJ" << std::endl;

    Matrix a(n, n);
    Matrix b(n, n);

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            a(i, j) = 1.0f;
        }
    }

    for (std::size_t i = 0; i < b.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            b(i, j) = 1.0f;
        }
    }

    {
        Matrix c = MatMulIKJ(a, b);
        std::cout << "test value c(0,0): " << c(0, 0) << std::endl;
    }
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMulIKJ(a, b);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        resultTime += elapsedMs;
        std::cout << "Attempt " << (i + 1) << ": " << elapsedMs << " ms"
                  << ", result(0, 0): " << result(0, 0) << '\n';
    }
    // std::cout << "Time: " << elapsedMs << " ms\n";
    // std::cout << "Result(0, 0): " << result(0, 0) << '\n';
    std::cout << "Matrix size: " << n << std::endl;
    std::cout << "Average time: " << (resultTime / 5.0) << " ms" << std::endl;
}

int main()
{
    RunBanchmark(128);
    RunBanchmarkIKJ(128);
    RunBanchmark(256);
    RunBanchmarkIKJ(256);
    RunBanchmark(512);
    RunBanchmarkIKJ(512);
    RunBanchmark(1024);
    RunBanchmarkIKJ(1024);
}
