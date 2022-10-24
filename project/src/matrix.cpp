#include <matrix.hpp>
#include <cassert>


template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix(const std::initializer_list<vector_line<T, M>>& list) : vector_matrix<T, N, M>()
{
    size_t i = 0;
    for (auto vec : list)
        for (size_t j = 0; j < vec.size(); ++j)
        {
            *this[i] = list[j];
            ++i;
        }
}

template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix(const std::initializer_list<vector_column<T, N>>& list)
{
    size_t i = 0;
    for (auto vec : list)
    {
        for (size_t j = 0; j < vec.size(); ++j)
            *this[j * this->col_size() + i] = list[j];
        ++i;
    }
        
}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::line(size_t line_index)
{
    vector_line<T, M> row;
    for(size_t i = 0; i < row.size(); ++i)
        row[i] = *this[line_index * this->col_size() + i];
    return row;
}

template<typename T, size_t N, size_t M>
vector_column<T, N> matrix<T, N, M>::column(size_t col_index)
{
    vector_column<T, N> col;
    for(size_t i = 0; i < col.size(); ++i)
        col[i] = *this[i * this->col_size() + col_index];
    return col;
}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::main_diagonal()
{
    size_t c_s = this->col_size(), l_s = this->line_size();
    assert("Matrix is not square!" &&  c_s == l_s);
    vector_line<T, M> row;
    for(size_t i = 0; i < row.size(); ++i)
        row[i] = *this[i * this->col_size() + i];
    return row;
}

template<typename T, size_t N, size_t M>
vector_line<T, M> matrix<T, N, M>::secondary_diagonal()
{
    size_t c_s = this->col_size(), l_s = this->line_size();
    assert("Matrix is not square!" && c_s == l_s);
    vector_line<T, M> row;
    for(size_t i = 0; i < row.size(); ++i)
        row[i] = *this[i * this->col_size() + this->col_size() - i];
    return row;
}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sum_line(const vector_line<T, M>& line_vec, size_t line_index)
{
    matrix copy = matrix(*this); 
    for (size_t i = 0; i < copy.col_size(); ++i)
        copy[line_index * copy.col_size() + i] += line_vec[i];
    return copy;
}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sum_col(const vector_column<T, N>& col_vec, size_t col_index)
{
    matrix copy = matrix(*this); 
    for (size_t i = 0; i < copy.line_size(); ++i)
        copy[i * copy.col_size() + col_index] += col_vec[i];
    return copy;
}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sub_line(const vector_line<T, M>& line_vec, size_t line_index)
{
    matrix copy = matrix(*this); 
    for (size_t i = 0; i < copy.col_size(); ++i)
        copy[line_index * copy.col_size() + i] -= line_vec[i];
    return copy;
}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::sub_col(const vector_column<T, N>& col_vec, size_t col_index)
{
    matrix copy = matrix(*this); 
    for (size_t i = 0; i < copy.line_size(); ++i)
        copy[i * copy.col_size() + col_index] -= col_vec[i];
    return copy;
}

template<typename T, size_t N, size_t M>
T matrix<T, N, M>::determinant()
{

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::inverse()
{

}
