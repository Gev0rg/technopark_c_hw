#pragma once

#include <iostream>
#include <vector>

#include <vector_matrix.hpp>

template <typename T, size_t N>
class vector_column : public vector_matrix<T, N, 1> { };