#pragma once

#include <iostream>
#include <vector>

#include <vector_column.hpp>

template <typename T, size_t N, size_t M>
class matrix {

public:

    matrix(std::initializer_list<T> list);
    matrix(std::initializer_list<vector_line<T, M>> list);
    matrix(const matrix& other);
    matrix& operator=(const matrix& other);
    matrix& operator+=(const matrix& other);
    matrix& operator-=(const matrix& other);
    matrix& operator*=(const matrix& other);
    matrix& operator/=(const matrix& other);
    matrix operator+(const matrix& other);
    matrix operator-(const matrix& other);
    matrix operator*(const matrix& other);
    matrix operator/(const matrix& other);
    vector_line<T, M> operator[](size_t index);
    vector_column<T, N> operator*(const vector_column<T, M>& vec);
    matrix operator*(T arg);
    vector_line<T, M> line(size_t line_index);
    vector_column<T, N> column(size_t col_index);
    vector_line<T, N> main_diagonal();
    vector_line<T, N> secondary_diagonal();
    matrix sum_line(const vector_line<T, M>& line_vec, size_t line_index);
    matrix sum_col(const vector_column<T, N>& col_vec, size_t col_index);
    matrix sub_line(const vector_line<T, M>& line_vec, size_t line_index);
    matrix sub_col(const vector_column<T, N>& col_vec, size_t col_index);
    matrix<T, M, N> transp();
    matrix inverse();
    T determinant();
    // matrix<T, (line_end - line_begin), (col_end - col_begin)> slice(size_t line_begin, size_t line_end, size_t col_begin, size_t col_end);

private:

    std::vector<T> mat;
    size_t _size_line;
    size_t _size_col;

};

template <typename T, size_t N, size_t M>
matrix<T, N, M> operator*(T arg, matrix<T, N, M> mat);