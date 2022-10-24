#pragma once

#include <iostream>
#include <vector>

#include <vector_matrix.hpp>

template <typename T, size_t M>
class vector_line : public vector_matrix<T, 1, M> 
{ 

    vector_line();

    vector_line(const std::initializer_list<T>& list);

};