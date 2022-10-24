#pragma once

#include <iostream>
#include <vector>

#include <vector_matrix.hpp>

template <typename T, size_t N>
class vector_column : public vector_matrix<T, N, 1> 
{ 
    
    vector_column();

    vector_column(const std::initializer_list<T>& list);

};