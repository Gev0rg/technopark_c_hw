#pragma once

#include <iostream>
#include <vector>

template <typename T, size_t N, size_t M>
class vector_matrix {

public:

    vector_matrix(std::initializer_list<T> list);

    vector_matrix(const vector_matrix& other);
    
    vector_matrix& operator=(const vector_matrix& other);

    vector_matrix& operator+=(const vector_matrix& other);

    vector_matrix& operator-=(const vector_matrix& other);

    vector_matrix& operator*=(const vector_matrix& other);

    vector_matrix& operator/=(const vector_matrix& other);

    vector_matrix operator+(const vector_matrix& other);

    vector_matrix operator-(const vector_matrix& other);

    vector_matrix operator*(const vector_matrix& other);

    vector_matrix operator/(const vector_matrix& other);

    vector_matrix operator*(T arg);

    T operator[](size_t index);

    vector_matrix slice(size_t begin, size_t end);

    size_t line_size();

    size_t col_size();

    std::vector<T> arr();

private:

    std::vector<T> _arr;

    size_t _line_size = N;

    size_t _col_size = M;
    
};

template <typename T, size_t N, size_t M>
vector_matrix<T, N, M> operator*(T arg, vector_matrix<T, N, M> other);