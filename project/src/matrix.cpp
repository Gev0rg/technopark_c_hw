#include <matrix.hpp>
#include <cassert>
#include <vector>
#include <cmath>


template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix() : vector_matrix<T, N, M>() { }

template<typename T, size_t N, size_t M>
matrix<T, N, M>::matrix(const std::initializer_list<T>& list) : vector_matrix<T, N, M>(list) { }

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
matrix<T, N - 1, M - 1> minor(matrix<T, N, M>& mat, size_t row, size_t col)
{

    matrix<T, mat.col_size() - 1, mat.col_size() - 1> _minor;

    for (size_t i = 0, ti = 0; i < mat.col_size(); i++) {

        if (i != row)
        {

            for (size_t j = 0, tj = 0; j < mat.col_size(); j++) {

                if (j != col)

                    continue;

                _minor[ti * _minor.col_size() + tj] = mat[i * mat.col_size() + j];

                ++tj;

            }

            ++ti;
            
        }

    }

    return _minor;

}

template<typename T, size_t N, size_t M>
T matrix<T, N, M>::determinant()
{

    size_t constexpr col_sz = this->col_size(), l_s = this->line_size();

    assert("Matrix is not square!" && col_sz == l_s);

    if (col_sz == 1)

            return (*this)[0];

        else if (col_sz == 2)

            return (*this)[0] * (*this)[3] - (*this)[1] * (*this)[2];

        else {

            T _determinant = 0;

            for (size_t k = 0; k < col_sz; k++) {

                matrix<T, l_s - 1, col_sz - 1> _minor = minor(*this, 1, k);

                _determinant += pow(-1, k + 2) * (*this)[k] * _minor.determinant();

            }

            return _determinant;

        }

}

template<typename T, size_t N, size_t M>
matrix<T, N, M> matrix<T, N, M>::inverse()
{
    size_t constexpr col_sz = this->col_size(), l_s = this->line_size();

    assert("Matrix is not square!" && col_sz == l_s);

    size_t det = this->determinant();

    assert("Matrix has no inverse!" && det != 0);

    matrix<T, M, N> inv;

    matrix<T, M, N> tran = this->transp();

    matrix<T, M, N> dop_tran;

    for(size_t i = 0; i < tran.col_size(); ++i)
    {
        for(size_t j = 0; j < tran.col_size(); ++i)
        {
            dop_tran[i * inv.col_size + j] = pow(-1, i + j + 2) * minor(tran, i, j);
        }
    }

    inv = dop_tran * det;

    return inv;
}
