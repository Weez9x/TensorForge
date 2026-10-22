#include "Matrix.h"
#include <cmath>
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

    Matrix resultIKJ = MatMulIKJ(a, b);

    Require(resultIKJ.Rows() == 2, "Wrong row count IKJ");
    Require(resultIKJ.Cols() == 2, "Wrong column count IKJ");

    Require(resultIKJ(0, 0) == 58.0f, "Wrong result(0, 0) IKJ");
    Require(resultIKJ(0, 1) == 64.0f, "Wrong result(0, 1) IKJ");
    Require(resultIKJ(1, 0) == 139.0f, "Wrong result(1, 0) IKJ");
    Require(resultIKJ(1, 1) == 154.0f, "Wrong result(1, 1) IKJ");

    Matrix resultBlocked = MatMulBlocked(a, b, 32);

    Require(resultBlocked.Rows() == 2, "Wrong row count Blocked");
    Require(resultBlocked.Cols() == 2, "Wrong column count Blocked");

    Require(resultBlocked(0, 0) == 58.0f, "Wrong result(0, 0) Blocked");
    Require(resultBlocked(0, 1) == 64.0f, "Wrong result(0, 1) Blocked");
    Require(resultBlocked(1, 0) == 139.0f, "Wrong result(1, 0) Blocked");
    Require(resultBlocked(1, 1) == 154.0f, "Wrong result(1, 1) Blocked");
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

    exceptionThrown = false;
    try
    {
        MatMulIKJ(c, d);
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    Require(exceptionThrown,
            "IKJ Expected invalid_argument for incompatible dimensions");

    exceptionThrown = false;
    try
    {
        MatMulBlocked(c, d, 64);
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    Require(exceptionThrown,
            "Blocked Expected invalid_argument for incompatible dimensions");
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

    Matrix resultIKJ = MatMulIKJ(a, identity);

    Require(resultIKJ.Rows() == a.Rows(), "Wrong row count IKJ");
    Require(resultIKJ.Cols() == a.Cols(), "Wrong column count IKJ");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            Require(a(i, j) == resultIKJ(i, j), "Wrong result IKJ");
        }
    }

    Matrix resultBlocked = MatMulBlocked(a, identity, 32);

    Require(resultBlocked.Rows() == a.Rows(), "Wrong row count Blocked");
    Require(resultBlocked.Cols() == a.Cols(), "Wrong column count Blocked");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            Require(a(i, j) == resultBlocked(i, j), "Wrong result IKJ");
        }
    }
}

void TestBlockedMatchesIJK()
{
    Matrix a(67, 79);
    Matrix b(79, 53);

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < a.Cols(); j++)
        {
            a(i, j) = i + j;
        }
    }

    for (std::size_t i = 0; i < b.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            b(i, j) = i + j;
        }
    }

    Matrix result = MatMultipli(a, b);
    Matrix resultBlocked32 = MatMulBlocked(a, b, 32);

    Require(resultBlocked32.Rows() == a.Rows(), "wrong resultBlocked.Rows()");
    Require(resultBlocked32.Cols() == b.Cols(), "wrong resultBlocked.Cols()");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            Require(std::fabs(resultBlocked32(i, j) - result(i, j)) < 1e-4f,
                    "Blocked result differs from IJK");
        }
    }

    Matrix resultBlocked64 = MatMulBlocked(a, b, 64);

    Require(resultBlocked64.Rows() == a.Rows(), "wrong resultBlocked.Rows()");
    Require(resultBlocked64.Cols() == b.Cols(), "wrong resultBlocked.Cols()");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            Require(std::fabs(resultBlocked64(i, j) - result(i, j)) < 1e-4f,
                    "Blocked result differs from IJK");
        }
    }

    Matrix resultBlocked128 = MatMulBlocked(a, b, 128);

    Require(resultBlocked128.Rows() == a.Rows(), "wrong resultBlocked.Rows()");
    Require(resultBlocked128.Cols() == b.Cols(), "wrong resultBlocked.Cols()");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            Require(std::fabs(resultBlocked128(i, j) - result(i, j)) < 1e-4f,
                    "Blocked result differs from IJK");
        }
    }

    Matrix resultIKJ = MatMulIKJ(a, b);
    Require(resultIKJ.Rows() == a.Rows(), "wrong resultBlocked.Rows()");
    Require(resultIKJ.Cols() == b.Cols(), "wrong resultBlocked.Cols()");

    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            Require(std::fabs(resultIKJ(i, j) - result(i, j)) < 1e-4f,
                    "IKJ result differs from IJK");
        }
    }
}

void TestBlockedZeroBlockSize()
{
    Matrix a(2, 3);
    Matrix b(3, 2);

    bool exceptionThrown = false;

    try
    {
        MatMulBlocked(a, b, 0);
    }
    catch (const std::invalid_argument &)
    {
        exceptionThrown = true;
    }

    Require(exceptionThrown, "Expected invalid_argument for zero block size");
}

int main()
{
    try
    {
        TestMatMultipli();
        TestIncompatibleDimensions();
        TestMultiplyByIdentity();
        TestBlockedMatchesIJK();
        TestBlockedZeroBlockSize();
        std::cout << "All tests passed\n";
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "Test failed: " << error.what() << '\n';
        return 1;
    }
}
