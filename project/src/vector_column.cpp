#include <vector_column.hpp>


template<typename T, size_t N>
vector_column<T, N>::vector_column(const std::initializer_list<T>& list) : vector_matrix<T, N, 1>(list){ }

template<typename T, size_t N>
vector_column<T, N>::vector_column() : vector_matrix<T, N, 1>() { }