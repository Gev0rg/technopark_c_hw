#include <vector_line.hpp>


template<typename T, size_t M>
vector_line<T, M>::vector_line(const std::initializer_list<T>& list) : vector_matrix<T, 1, M>(list){ }

template<typename T, size_t M>
vector_line<T, M>::vector_line() : vector_matrix<T, 1, M>() { }
