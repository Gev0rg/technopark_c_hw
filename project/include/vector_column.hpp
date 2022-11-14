#pragma once

#include "vector_matrix.hpp"

template <typename T, size_t row_num>
class vector_column : public vector_matrix<T, row_num, 1> 
{ 
    vector_column() = default;
    template<typename... Type>
    vector_column(Type...);
};

template<typename T, size_t row_num>
template<typename... Type>
vector_column<T, row_num>::vector_column(Type... init_list) : vector_matrix<T, row_num, 1>(init_list...) { } // так правильно?
