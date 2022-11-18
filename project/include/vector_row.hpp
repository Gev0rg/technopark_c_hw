#pragma once

#include "matrix.hpp"

template <typename T, size_t col_num>
class vector_row : public matrix<T, 1, col_num> 
{ 
public:

    vector_row() = default;
    template<typename... Type>
    vector_row(Type...);

    using matrix<T, 1, col_num>::operator();
    T& operator()(size_t);
    const T& operator()(size_t) const;

    template <size_t begin_col, size_t end_col>
    vector_row<T, end_col - begin_col> slice() const; 
};

template<typename T, size_t col_num>
template<typename... Type>
vector_row<T, col_num>::vector_row(Type... init_list) : matrix<T, 1, col_num>(init_list...){ }

template<typename T, size_t col_num>
T& vector_row<T, col_num>::operator()(size_t col_index)
{
    return (*this)(0, col_index);
}

template<typename T, size_t col_num>
const T& vector_row<T, col_num>::operator()(size_t col_index) const
{
    return (*this)(0, col_index);
}

template<typename T, size_t col_num>
template <size_t begin_col, size_t end_col>
vector_row<T, end_col - begin_col> vector_row<T, col_num>::slice() const
{
    vector_row<T, end_col - begin_col> new_row;
    size_t k = 0;

    for(size_t i = begin_col; i < end_col; ++i) {
        new_row(k) = (*this)(i);
        ++k;
    }
    
    return new_row;
}
