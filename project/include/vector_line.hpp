#pragma once

#include <iostream>
#include <vector>

#include <vector_column.hpp>

template <typename T, size_t M>
class vector_line : public vector_matrix<T, 1, M> { };