#pragma once
#include <cstddef>
#include <vector>

class Matrix
{
    public:

        Matrix();
        Matrix(std::size_t rows, std::size_t cols);
        float &operator()(std::size_t row, std::size_t col);
        const float &operator()(std::size_t row, std::size_t col) const;
        std::size_t Rows() const;
        std::size_t Cols() const;
        const float *Data() const;
        float *Data();

    private:

        std::size_t rows_;
        std::size_t cols_;
        std::vector<float> data_;
};

Matrix MatMultipli(const Matrix &a, const Matrix &b);
Matrix MatMulIKJ(const Matrix &a, const Matrix &b);
Matrix MatMulBlocked(const Matrix &a, const Matrix &b, std::size_t blockSize);
