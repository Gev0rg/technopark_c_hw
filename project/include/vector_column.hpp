#pragma once

#include <iostream>
#include <vector>

template <typename T, size_t N, size_t M>
class matrix;

template <typename T, size_t M>
class vector_line;

template <typename T, size_t N>
class vector_column {

public:

    vector_column(std::initializer_list<T> list);
    vector_column(const vector_column& other);
    vector_column& operator=(const vector_column& other);
    vector_column& operator+=(const vector_column& other);
    vector_column& operator-=(const vector_column& other);
    vector_column& operator*=(const vector_column& other);
    vector_column& operator/=(const vector_column& other);
    vector_column operator+(const vector_column& other);
    vector_column operator-(const vector_column& other);
    vector_column operator*(const vector_column& other);
    vector_column operator/(const vector_column& other);
    T operator[](size_t index);
    template <size_t M>
    matrix<T, N, M> operator*(const vector_line<T, M>& other_vec);
    vector_column operator*(T arg);
    vector_column slice(size_t begin, size_t end);
    size_t size();

private:

    std::vector<T> vec;
    size_t _size;

};

template <typename T, size_t N>
vector_column<T, N> operator*(T arg, vector_column<T, N> vec);