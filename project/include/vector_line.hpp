#pragma once

#include "vector_matrix.hpp"

template <typename T, size_t M>
class vector_line : public vector_matrix<T, 1, M> 
{ 
    vector_line() = default;
    template<typename... Type>
    vector_line(Type...);
};

template<typename T, size_t M>
template<typename... Type>
vector_line<T, M>::vector_line(Type... init_list) : vector_matrix<T, 1, M>(init_list...){ } // так правильно?
