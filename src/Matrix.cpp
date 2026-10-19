#include <Matrix.h>
#include <cassert>
#include <cstddef>
#include <limits>
#include <stdexcept>

Matrix::Matrix() : rows_(0), cols_(0)
{
}

Matrix::Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols)
{
    if (cols != 0 && rows > std::numeric_limits<std::size_t>::max() / cols)
    {
        throw std::length_error("Matrix dimesions overflow!");
    }
    data_.resize(rows * cols, 0.0f);
}

float &Matrix::operator()(std::size_t row, std::size_t col)
{
    assert(row < rows_ && col < cols_);
    return data_[row * cols_ + col];
}

const float &Matrix::operator()(std::size_t row, std::size_t col) const
{
    assert(row < rows_ && col < cols_);
    return data_[row * cols_ + col];
}

Matrix MatMultipli(const Matrix &a, const Matrix &b)
{
    if (a.Cols() != b.Rows())
    {
        throw std::invalid_argument("Cols A != Rows B");
    }
    Matrix result(a.Rows(), b.Cols());
    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t j = 0; j < b.Cols(); j++)
        {
            for (std::size_t k = 0; k < a.Cols(); k++)
            {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return result;
}

Matrix MatMulIKJ(const Matrix &a, const Matrix &b)
{
    if (a.Cols() != b.Rows())
    {
        throw std::invalid_argument("Cols A != Rows B");
    }
    Matrix result(a.Rows(), b.Cols());
    for (std::size_t i = 0; i < a.Rows(); i++)
    {
        for (std::size_t k = 0; k < a.Cols(); k++)
        {
            for (std::size_t j = 0; j < b.Cols(); j++)
            {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return result;
}

std::size_t Matrix::Rows() const
{
    return rows_;
}

std::size_t Matrix::Cols() const
{
    return cols_;
}

float *Matrix::Data()
{
    return data_.data();
}

const float *Matrix::Data() const
{
    return data_.data();
}
