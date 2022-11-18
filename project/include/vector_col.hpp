#pragma once

#include "matrix.hpp"

template <typename T, size_t row_num>
class vector_col : public matrix<T, row_num, 1> 
{ 
public:

    vector_col() = default;
    template<typename... Type>
    vector_col(Type...);

    using matrix<T, row_num, 1>::operator();
    T& operator()(size_t);
    const T& operator()(size_t) const;

    template <ssize_t begin_row, size_t end_row>
    vector_col<T, end_row - begin_row> slice() const; 

};

template<typename T, size_t row_num>
template<typename... Type>
vector_col<T, row_num>::vector_col(Type... init_list) : matrix<T, row_num, 1>(init_list...) { }

template<typename T, size_t row_num>
T& vector_col<T, row_num>::operator()(size_t row_index)
{
    return (*this)(0, row_index);
}

template<typename T, size_t row_num>
const T& vector_col<T, row_num>::operator()(size_t row_index) const
{
    return (*this)(0, row_index);
}

template<typename T, size_t row_num>
template <ssize_t begin_row, size_t end_row>
vector_col<T, end_row - begin_row> vector_col<T, row_num>::slice() const
{
    vector_col<T, end_row - begin_row> new_col;
    size_t k = 0;

    for(size_t i = begin_row; i < end_row; ++i) {
        new_col(k) = (*this)(i);
        ++k;
    }

    return new_col;
}
