#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <array>
#include <cstddef>

template<size_t rows, size_t cols>
struct Matrix{

    std::array<std::array<double, cols>, rows> m_matrix; 
    
    //size_t m_rows;
    //size_t m_cols;

    constexpr Matrix(){
        for(auto& row : m_matrix){
            row.fill(0.0);
        }
    };

    constexpr Matrix<rows, cols>& scale_by_value(double value){           // return type is not void to enable chaining
        for(size_t i = 0; i < rows ; i++){
            for(size_t j = 0 ; j < cols; j++){
                m_matrix[i][j] = m_matrix[i][j] * value;
            }
        }
        return *this;
    }

    constexpr Matrix<rows, cols>& add_value(double value){
        for(size_t i = 0; i < rows ; i++){
            for(size_t j = 0 ; j < cols; j++){
                m_matrix[i][j] = m_matrix[i][j] + value;
            }
        }
        return *this;
    }

    constexpr Matrix<cols, rows> transpose(){
        Matrix<cols, rows> transposed;
        for(size_t i = 0; i < rows ; i++){
            for(size_t j = 0 ; j < cols; j++){
                transposed.m_matrix[j][i] = m_matrix[i][j];
            }
        }
        return transposed;
    }

    constexpr Matrix<rows, cols> apply_sigmoid(){
        Matrix<rows, cols> result_matrix;
        for(size_t i = 0; i < rows ; i++){
            for(size_t j = 0; j < cols; j++){
                result_matrix.m_matrix[i][j] =  (1.0 / (1.0 + std::exp(-1 * m_matrix[i][j])));
            }
        }
        return result_matrix;
    }

    constexpr Matrix<rows, cols> apply_sigmoid_prime(){
        Matrix<rows, cols> unit_matrix;
        for(auto& row : unit_matrix.m_matrix) row.fill(1.0);
        return *this % (unit_matrix - *this);
    }
};

//helper fns

template<size_t r1, size_t c1, size_t c2>
constexpr Matrix<r1, c2> operator*(const Matrix<r1, c1>& matrix1, const Matrix<c1, c2>& matrix2){
    Matrix<r1, c2> result_matrix;
    
    for(size_t i = 0; i < r1; i++){
        for(size_t j = 0; j < c2 ; j++){
            double sum = 0.0;
            for(size_t k = 0 ; k < c1; k++){
                sum += matrix1.m_matrix[i][k] * matrix2.m_matrix[k][j];
            }
            result_matrix.m_matrix[i][j] = sum;
        }
    }

    return result_matrix;
}

template<size_t r, size_t c>
constexpr Matrix<r, c> operator+(const Matrix<r, c>& matrix1, const Matrix<r, c>& matrix2){
    Matrix<r, c> result_matrix;
    
    for(size_t i = 0; i < r; i++){
        for(size_t j = 0; j < c ; j++){
            result_matrix.m_matrix[i][j] = matrix1.m_matrix[i][j] + matrix2.m_matrix[i][j];
        }
    }

    return result_matrix;
}

template<size_t r, size_t c>
constexpr Matrix<r, c> operator-(const Matrix<r, c>& matrix1, const Matrix<r, c>& matrix2){
    Matrix<r, c> result_matrix;
    
    for(size_t i = 0; i < r; i++){
        for(size_t j = 0; j < c ; j++){
            result_matrix.m_matrix[i][j] = matrix1.m_matrix[i][j] - matrix2.m_matrix[i][j];
        }
    }

    return result_matrix;
}

template<size_t r, size_t c>
constexpr Matrix<r, c> operator%(const Matrix<r, c>& matrix1, const Matrix<r, c>& matrix2){   // element by element multiplicaton
    Matrix<r, c> result_matrix;
    
    for(size_t i = 0; i < r; i++){
        for(size_t j = 0; j < c ; j++){
            result_matrix.m_matrix[i][j] = matrix1.m_matrix[i][j] * matrix2.m_matrix[i][j];
        }
    }

    return result_matrix;
}

#endif