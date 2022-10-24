#include <vector_matrix.hpp>
#include <cassert>


template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix() : _line_size(N), _col_size(M), _size(N * M)
{
    _arr.reserve(_size);
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix(const std::initializer_list<T>& list) : _line_size(N), _col_size(M), _size(N * M)
{   
    assert("The number of elements does not match the size of the matrix!" && _size == list.size());
    _arr = list;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix(const vector_matrix& other) : 
_line_size(other.line_size()), _col_size(other.col_size()), _size(other.size()), _arr(other.arr()) 
{ }

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator=(const vector_matrix& other)
{
    size_t c_s = other.col_size(), l_s = other.line_size();
    assert("Matrices have different dimensions!" && _line_size == l_s && _col_size == c_s);
    _arr = other.arr();
    return *this;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator+=(const vector_matrix& other)
{
    size_t c_s = this->col_size(), l_s = this->line_size();
    assert("Matrices have different dimensions!" && _line_size == l_s && _col_size == c_s);
    for (size_t i = 0; i < _size; ++i) 
        _arr[i] += other[i]; 
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator-=(const vector_matrix& other)
{
    size_t c_s = this->col_size(), l_s = this->line_size();
    assert("Matrices have different dimensions!" && _line_size == l_s && _col_size == c_s);
    for (size_t i = 0; i < _size; ++i) 
        _arr[i] -= other[i]; 
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator*=(const vector_matrix& other)
{
    size_t c_s = this->col_size(), l_s = this->line_size();
    assert("Matrices have different dimensions!" && _line_size == l_s && _col_size == c_s);
    for (size_t i = 0; i < _size; ++i) 
        _arr[i] *= other[i]; 
    return *this;  
}

template<typename T, size_t N, size_t M>
template<size_t L>
vector_matrix<T, N, L> vector_matrix<T, N, M>::mul(const vector_matrix<T, M, L>& other)
{
    size_t l_s = other.line_size();
    assert("Matrices cannot be multiplied!" && _col_size == l_s);
    vector_matrix<T, this->_line_size, other.col_size()> time_obj;
    for(size_t i = 0; i < time_obj.line_size(); ++i)
        for(size_t j = 0; j < time_obj.col_size(); ++j)
            for(size_t k = 0; k < _col_size; k++)
                time_obj[i * time_obj.col_size() + j] += _arr[i * _col_size + k] * other[k * other.col_size() + j];
    return time_obj;
}


template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator+(const vector_matrix& other) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    copy += other;
    return copy;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator-(const vector_matrix& other) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    copy -= other;
    return copy;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator*(const vector_matrix& other) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    copy *= other;
    return copy; 
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator*=(const T& arg)
{
    for(size_t i = 0; i < _size; ++i)
        _arr[i] *= arg;
    return *this;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator*(const T& arg) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    copy *= arg;
    return copy; 
}

template<typename T, size_t N, size_t M>
T& vector_matrix<T, N, M>::operator[](size_t index)
{
    return _arr[index];
}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::line_size() const
{
    return _line_size;
}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::col_size() const
{
    return _col_size;
}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::size() const
{
    return _size;
}

template<typename T, size_t N, size_t M>
std::vector<T> vector_matrix<T, N, M>::arr() const
{
    return _arr;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, M, N> vector_matrix<T, N, M>::transp() const
{
    vector_matrix<T, M, N> transp;
    for (size_t i = 0; i < _line_size; ++i)
        for (size_t j = 0; j < _col_size; ++j)
            transp[j * transp.col_size + i] = *this[i * _col_size + j];
    return transp;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> operator*(const T& arg, const vector_matrix<T, N, M>& other)
{
    vector_matrix<T, N, M> copy = vector_matrix<T, N, M>(other);
    copy *= arg;
    return copy;
}

template<typename T, size_t N, size_t M>
template<size_t begin_col, size_t end_col, size_t begin_line, size_t end_line>
vector_matrix<T, end_line - begin_line, end_col - begin_col> vector_matrix<T, N, M>::slice() const
{
    vector_matrix<T, end_line - begin_line, end_col - begin_col> new_mat;
    size_t k = 0;
    for(size_t i = begin_line; i < end_line; ++i)
    {
        for(size_t j = begin_col; j < end_col; ++j) 
        {
            new_mat[k] = _arr[i * _col_size + j];
            ++k;
        }
    }
    return new_mat;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator+=(const T& arg)
{
    for(size_t i = 0; i < _size; ++i)
        _arr[i] += arg;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator+(const T& arg) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    for(size_t i = 0; i < _size; ++i)
        copy[i] += arg;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator-=(const T& arg)
{
    for(size_t i = 0; i < _size; ++i)
        _arr[i] -= arg;
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator-(const T& arg) const
{
    vector_matrix copy = vector_matrix<T, N, M>(*this);
    for(size_t i = 0; i < _size; ++i)
        copy[i] -= arg;
}
