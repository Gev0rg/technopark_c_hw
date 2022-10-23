#pragma once

#include <iostream>
#include <vector>

#include <vector_matrix.hpp>
#include <vector_line.hpp>
#include <vector_column.hpp>

template <typename T, size_t N, size_t M>
class matrix : public vector_matrix<T, N, M> {

public:

    vector_line<T, M> line(size_t line_index);

    vector_column<T, N> column(size_t col_index);

    vector_line<T, M> main_diagonal();

    vector_line<T, M> secondary_diagonal();

    matrix sum_line(const vector_line<T, M>& line_vec, size_t line_index);

    matrix sum_col(const vector_column<T, N>& col_vec, size_t col_index);

    matrix sub_line(const vector_line<T, M>& line_vec, size_t line_index);

    matrix sub_col(const vector_column<T, N>& col_vec, size_t col_index);

    matrix transp();

    matrix inverse();

    T determinant();

    vector_line<T, M> operator[](size_t index);

    matrix(std::initializer_list<vector_line<T, M>> list);

    matrix(std::initializer_list<vector_column<T, N>> list);
    
    matrix slice(size_t line_begin, size_t line_end, size_t col_begin, size_t col_end);

};