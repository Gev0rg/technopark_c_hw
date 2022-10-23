#pragma once

#include <iostream>
#include <vector>

#include <matrix.hpp>

template <typename T, size_t M>
class vector_line {

public:

    vector_line(std::initializer_list<T> list);
    vector_line(const vector_line& other);
    vector_line& operator=(const vector_line& other);
    vector_line& operator+=(const vector_line& other);
    vector_line& operator-=(const vector_line& other);
    vector_line& operator*=(const vector_line& other);
    vector_line& operator/=(const vector_line& other);
    vector_line operator+(const vector_line& other);
    vector_line operator-(const vector_line& other);
    vector_line operator*(const vector_line& other);
    vector_line operator/(const vector_line& other);
    T operator[](size_t index);
    template <size_t N>
    vector_line operator*(const matrix<T, M, N>& mat);
    T operator*(const vector_column<T, M>& other_vec);
    vector_line operator*(T arg);
    vector_line slice(size_t begin, size_t end);
    size_t size();

private:

    std::vector<T> vec;
    size_t _size;

};

template <typename T, size_t M>
vector_line<T, M> operator*(T arg, vector_line<T, M> vec);