#pragma once

#include <iostream>
#include <vector>

template <typename T, size_t N, size_t M>
class vector_matrix 
{

public:

    vector_matrix();

    vector_matrix(std::initializer_list<T> list);

    vector_matrix(const vector_matrix& other);
    
    vector_matrix& operator=(const vector_matrix& other);

    vector_matrix& operator+=(const vector_matrix& other);

    vector_matrix& operator-=(const vector_matrix& other);

    vector_matrix& operator*=(const vector_matrix& other);

    vector_matrix operator+(const vector_matrix& other);

    vector_matrix operator-(const vector_matrix& other);

    vector_matrix operator*(const vector_matrix& other);

    vector_matrix operator+=(const T& arg);

    vector_matrix operator+(const T& arg);

    vector_matrix operator-=(const T& arg);

    vector_matrix operator-(const T& arg);

    vector_matrix operator*=(const T& arg);

    vector_matrix operator*(const T& arg);

    T& operator[](size_t index);

    template <size_t begin_col, size_t end_col, size_t begin_line = 0, size_t end_line = 1>
    vector_matrix<T, end_line - begin_line, end_col - begin_col> slice();

    vector_matrix<T, M, N> transp();

    size_t line_size();

    size_t col_size();

    size_t size();

    std::vector<T> arr();

private:

    std::vector<T> _arr;

    size_t _line_size;

    size_t _col_size;

    size_t _size;
    
};

template <typename T, size_t N, size_t M>
vector_matrix<T, N, M> operator*(const T& arg, const vector_matrix<T, N, M>& other);