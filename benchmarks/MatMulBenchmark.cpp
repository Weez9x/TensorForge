#include "Matrix.h"
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct BenchmarkResult
{
        std::size_t matrixSize;
        std::string algorithm;
        std::string config;
        double averageMs;
};

double RunBanchmark(std::size_t n)
{
    std::cout << "Test IJK " << n << std::endl;
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
    double checkSum = 0.0f;
    Matrix c = MatMultipli(a, b);
    checkSum += c(0, 0);
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMultipli(a, b);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        resultTime += elapsedMs;
        checkSum += result(0, 0);
    }
    std::cout << n << " checkSum = " << checkSum << std::endl;
    return resultTime / 5.0;
}

double RunBanchmarkIKJ(std::size_t n)
{
    std::cout << "Test IKJ " << n << std::endl;

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

    double checkSum = 0.0f;
    Matrix c = MatMulIKJ(a, b);
    checkSum += c(0, 0);
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMulIKJ(a, b);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        checkSum += result(0, 0);
        resultTime += elapsedMs;
    }
    std::cout << n << " checkSum = " << checkSum << std::endl;
    return (resultTime / 5.0f);
}

double RunBanchmarkIKJBlocked(std::size_t n, std::size_t blockSize)
{
    std::cout << "Test IKJ" << n << "Blocked " << blockSize << std::endl;

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

    double checkSum = 0.0f;
    Matrix c = MatMulBlocked(a, b, blockSize);
    checkSum += c(0, 0);
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMulBlocked(a, b, blockSize);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        checkSum += result(0, 0);
        resultTime += elapsedMs;
    }
    std::cout << n << " checkSum = " << checkSum << std::endl;
    return (resultTime / 5.0f);
}

double RunBanchmarkParallel(std::size_t n, std::size_t threadsCount)
{
    std::cout << "Test IKJ" << n << "Parallel threads " << threadsCount
              << std::endl;

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

    double checkSum = 0.0f;
    Matrix c = MatMulIKJParallel(a, b, threadsCount);
    checkSum += c(0, 0);
    double resultTime = 0.0;

    for (int i = 0; i < 5; i++)
    {
        const auto start = std::chrono::steady_clock::now();
        Matrix result = MatMulIKJParallel(a, b, threadsCount);
        const auto finish = std::chrono::steady_clock::now();
        const double elapsedMs =
            std::chrono::duration<double, std::milli>(finish - start).count();
        checkSum += result(0, 0);
        resultTime += elapsedMs;
    }
    std::cout << n << " checkSum = " << checkSum << std::endl;
    return (resultTime / 5.0f);
}

int main()
{
    std::vector<BenchmarkResult> result;
    result.push_back({128, "IJK", "-", RunBanchmark(128)});
    result.push_back({128, "IKJ", "-", RunBanchmarkIKJ(128)});
    result.push_back(
        {128, "Blocked", "block=32", RunBanchmarkIKJBlocked(128, 32)});
    result.push_back(
        {128, "Blocked", "block=64", RunBanchmarkIKJBlocked(128, 64)});
    result.push_back(
        {128, "Parallel", "threads=1", RunBanchmarkParallel(128, 1)});
    result.push_back(
        {128, "Parallel", "threads=2", RunBanchmarkParallel(128, 2)});
    result.push_back(
        {128, "Parallel", "threads=4", RunBanchmarkParallel(128, 4)});
    result.push_back(
        {128, "Parallel", "threads=8", RunBanchmarkParallel(128, 8)});
    result.push_back({256, "IJK", "-", RunBanchmark(256)});
    result.push_back({256, "IKJ", "-", RunBanchmarkIKJ(256)});
    result.push_back(
        {256, "Blocked", "block=32", RunBanchmarkIKJBlocked(256, 32)});
    result.push_back(
        {256, "Blocked", "block=64", RunBanchmarkIKJBlocked(256, 64)});
    result.push_back(
        {256, "Parallel", "threads=1", RunBanchmarkParallel(256, 1)});
    result.push_back(
        {256, "Parallel", "threads=2", RunBanchmarkParallel(256, 2)});
    result.push_back(
        {256, "Parallel", "threads=4", RunBanchmarkParallel(256, 4)});
    result.push_back(
        {256, "Parallel", "threads=8", RunBanchmarkParallel(256, 8)});
    result.push_back({512, "IJK", "-", RunBanchmark(512)});
    result.push_back({512, "IKJ", "-", RunBanchmarkIKJ(512)});
    result.push_back(
        {512, "Blocked", "block=32", RunBanchmarkIKJBlocked(512, 32)});
    result.push_back(
        {512, "Blocked", "block=64", RunBanchmarkIKJBlocked(512, 64)});
    result.push_back(
        {512, "Parallel", "threads=1", RunBanchmarkParallel(512, 1)});
    result.push_back(
        {512, "Parallel", "threads=2", RunBanchmarkParallel(512, 2)});
    result.push_back(
        {512, "Parallel", "threads=4", RunBanchmarkParallel(512, 4)});
    result.push_back(
        {512, "Parallel", "threads=8", RunBanchmarkParallel(512, 8)});
    result.push_back({1024, "IJK", "-", RunBanchmark(1024)});
    result.push_back({1024, "IKJ", "-", RunBanchmarkIKJ(1024)});
    result.push_back(
        {1024, "Blocked", "block=32", RunBanchmarkIKJBlocked(1024, 32)});
    result.push_back(
        {1024, "Blocked", "block=64", RunBanchmarkIKJBlocked(1024, 64)});
    result.push_back(
        {1024, "Parallel", "threads=1", RunBanchmarkParallel(1024, 1)});
    result.push_back(
        {1024, "Parallel", "threads=2", RunBanchmarkParallel(1024, 2)});
    result.push_back(
        {1024, "Parallel", "threads=4", RunBanchmarkParallel(1024, 4)});
    result.push_back(
        {1024, "Parallel", "threads=8", RunBanchmarkParallel(1024, 8)});
    std::cout << std::left << std::setw(10) << "Size" << std::setw(20)
              << "Algorithm" << std::setw(16) << "Config" << std::right
              << std::setw(14) << "Average, ms" << '\n';

    std::cout << std::string(60, '-') << '\n';

    for (const auto &row : result)
    {
        std::cout << std::left << std::setw(10) << row.matrixSize
                  << std::setw(20) << row.algorithm << std::setw(16)
                  << row.config << std::right << std::setw(14) << std::fixed
                  << std::setprecision(3) << row.averageMs << '\n';
    }
}
