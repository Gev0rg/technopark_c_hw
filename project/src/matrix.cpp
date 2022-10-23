#include <matrix.hpp>


template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix(std::initializer_list<vector_column<T, N>> list)
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::slice(size_t line_begin, size_t line_end, size_t col_begin, size_t col_end)
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix(std::initializer_list<vector_line<T, M>> list)
{

}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::operator[](size_t index)
{

}

template<typename T, size_t N, size_t M>
T matrix<T, N, M>::determinant()
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::inverse()
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::transp()
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sub_col(const vector_column<T, N>& col_vec, size_t col_index)
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sub_line(const vector_line<T, M>& line_vec, size_t line_index)
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sum_col(const vector_column<T, N>& col_vec, size_t col_index)
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sum_line(const vector_line<T, M>& line_vec, size_t line_index)
{

}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::secondary_diagonal()
{

}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::main_diagonal()
{

}

template<typename T, size_t N, size_t M>
vector_column<T, N> matrix<T, N, M>::column(size_t col_index)
{

}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::line(size_t line_index)
{

}
