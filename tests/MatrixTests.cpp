#include "Matrix.h"
#include <iostream>
#include <stdexcept>

void Require(bool condition, const char *message)
{
    if (!condition)
    {
        throw std::runtime_error(message);
    }
}

void TestMatMultipli()
{
    Matrix a(2, 3);
    Matrix b(3, 2);

    float value = 1.0f;
    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            a(i, j) = value;
            value += 1.0f;
        }
    }

    for (std::size_t i = 0; i < b.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            b(i, j) = value;
            value += 1.0f;
        }
    }

    Matrix result = MatMultipli(a, b);

    Require(result.Rows() == 2, "Wrong row count");
    Require(result.Cols() == 2, "Wrong column count");

    Require(result(0, 0) == 58.0f, "Wrong result(0, 0)");
    Require(result(0, 1) == 64.0f, "Wrong result(0, 1)");
    Require(result(1, 0) == 139.0f, "Wrong result(1, 0)");
    Require(result(1, 1) == 154.0f, "Wrong result(1, 1)");
}

void TestIncompatibleDimensions()
{
    Matrix c(3, 5);
    Matrix d(6, 9);

    bool exceptionThrown = false;

    try
    {
        MatMultipli(c, d);
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    Require(exceptionThrown,
            "Expected invalid_argument for incompatible dimensions");
}

void TestMultiplyByIdentity()
{
    Matrix a(2, 3);
    Matrix identity(3, 3);

    float value = 1.0f;
    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            a(i, j) = value;
            value += 1.0f;
        }
    }
    for (std::size_t i = 0; i < identity.Rows(); i++)
    {
        identity(i, i) = 1.0f;
    }
    Matrix result = MatMultipli(a, identity);

    Require(result.Rows() == a.Rows(), "Wrong row count");
    Require(result.Cols() == a.Cols(), "Wrong column count");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            Require(a(i, j) == result(i, j), "Wrong result");
        }
    }
}

int main()
{
    try
    {
        TestMatMultipli();
        TestIncompatibleDimensions();
        TestMultiplyByIdentity();
        std::cout << "All tests passed\n";
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "Test failed: " << error.what() << '\n';
        return 1;
    }
}
