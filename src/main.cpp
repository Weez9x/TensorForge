#include "Matrix.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    Matrix matrix_1(3, 4);
    for (std::size_t i = 0; i < matrix_1.Rows(); i++)
    {
        for (std::size_t j = 0; j < matrix_1.Cols(); j++)
        {
            matrix_1(i, j) = (i + 1) * (j + 1);
        }
    }
    std::cout << "Rows: " << matrix_1.Rows() << std::endl;
    std::cout << "Cols: " << matrix_1.Cols() << std::endl;
    std::cout << "Value:" << std::endl;
    for (std::size_t i = 0; i < matrix_1.Rows(); i++)
    {
        for (std::size_t j = 0; j < matrix_1.Cols(); j++)
        {
            std::cout << matrix_1(i, j) << " ";
        }
        std::cout << std::endl;
    }

    Matrix aM(2, 3);
    Matrix bM(3, 2);
    float value = 1.0f;
    for (std::size_t i = 0; i < aM.Rows(); i++)
    {
        for (std::size_t j = 0; j < aM.Cols(); j++)
        {
            aM(i, j) = value;
            value += 1.0f;
        }
    }

    for (std::size_t i = 0; i < bM.Rows(); i++)
    {
        for (std::size_t j = 0; j < bM.Cols(); j++)
        {
            bM(i, j) = value;
            value += 1.0f;
        }
    }
    std::cout << "Value: aM" << std::endl;
    for (std::size_t i = 0; i < aM.Rows(); i++)
    {
        for (std::size_t j = 0; j < aM.Cols(); j++)
        {
            std::cout << aM(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Value: bM" << std::endl;
    for (std::size_t i = 0; i < bM.Rows(); i++)
    {
        for (std::size_t j = 0; j < bM.Cols(); j++)
        {
            std::cout << bM(i, j) << " ";
        }
        std::cout << std::endl;
    }

    Matrix cM = MatMultipli(aM, bM);

    std::cout << "Value: cM" << std::endl;

    for (std::size_t i = 0; i < cM.Rows(); ++i)
    {
        for (std::size_t j = 0; j < cM.Cols(); ++j)
        {
            std::cout << cM(i, j) << " ";
        }
        std::cout << std::endl;
    }

    Matrix threadMul = MatMulIKJParallel(aM, bM, 2);
    std::cout << "MULthread: " << std::endl;
    for (std::size_t i = 0; i < threadMul.Rows(); i++)
    {
        for (std::size_t j = 0; j < threadMul.Cols(); j++)
        {
            std::cout << threadMul(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
