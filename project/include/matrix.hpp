#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

template <typename T, size_t col_num>
class vector_row;
template <typename T, size_t row_num>
class vector_col;

template <typename T, size_t row_num, size_t col_num>
class matrix 
{

public:

    matrix() = default;
    template<typename... Type>
    matrix(Type...);
    matrix(const matrix<T, row_num, col_num>&);
    matrix(const vector_row<T, col_num>&);
    matrix(const vector_col<T, row_num>&);
    matrix& operator=(const matrix<T, row_num, col_num>&);

    matrix& operator+=(const matrix<T, row_num, col_num>&);
    matrix& operator-=(const matrix<T, row_num, col_num>&);    

    matrix operator+(const matrix<T, row_num, col_num>&) const;
    matrix operator-(const matrix<T, row_num, col_num>&) const;
    matrix hadamard_prod(const matrix<T, row_num, col_num>&) const;
    
    template <size_t res_col_num>
    matrix<T, row_num, res_col_num> operator*(const matrix<T, col_num, res_col_num>&) const;

    matrix operator+=(const T&);
    matrix operator-=(const T&);
    matrix operator*=(const T&);

    matrix operator+(const T&) const;
    matrix operator-(const T&) const;
    matrix operator*(const T&) const;

    T& operator()(size_t, size_t);
    const T& operator()(size_t, size_t) const;

    template <size_t begin_col, size_t end_col, size_t begin_row, size_t end_row>
    matrix<T, end_row - begin_row, end_col - begin_col> slice() const; 

    matrix<T, col_num, row_num> get_transp() const;

    size_t get_row_size() const;
    size_t get_col_size() const;
    size_t get_size() const;

    vector_row<T, col_num> get_row(size_t) const;
    vector_col<T, row_num> get_col(size_t) const;

    vector_row<T, col_num>  get_main_diagonal() const;
    vector_row<T, col_num>  get_secondary_diagonal() const;

    matrix sum_to_each_row(const vector_row<T, col_num>&);
    matrix sum_to_each_col(const vector_col<T, row_num>&);
    matrix sub_to_each_row(const vector_row<T, col_num>&);
    matrix sub_to_each_col(const vector_col<T, row_num>&);
    
    T get_determinant() const;
    matrix get_inverse() const;

    bool operator==(matrix<T, row_num, col_num>&);

    void print() const;

private:

    std::array<T, row_num * col_num> _arr;
    
};

template<typename T, size_t row_num, size_t col_num>
void matrix<T, row_num, col_num>::print() const
{
    for (auto a: _arr) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

template<typename T, size_t row_num, size_t col_num>
bool matrix<T, row_num, col_num>::operator==(matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            if ((*this)(i, j) != other(i, j)) {
                return false;
            }
        }
    }
    
    return true;
}

template<typename T, size_t row_num, size_t col_num>
template<typename... Type>
matrix<T, row_num, col_num>::matrix(Type... init_list) : _arr({init_list...}) { }

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>::matrix(const matrix<T, row_num, col_num>& other) 
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) = other(i, j);
        }
    }
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>::matrix(const vector_row<T, col_num>& vec)
{
    size_t arr_index = 0;
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            _arr[arr_index++] = vec(0, j);
        }
    }
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>::matrix(const vector_col<T, row_num>& vec)
{
    size_t arr_index = 0;
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            _arr[arr_index++] = vec(0, i);
        }
    }
}

template<typename T, size_t row_num, size_t col_num>
T& matrix<T, row_num, col_num>::operator()(size_t row_index, size_t col_index) 
{
    return _arr[row_index * col_num + col_index];
}

template<typename T, size_t row_num, size_t col_num>
const T& matrix<T, row_num, col_num>::operator()(size_t row_index, size_t col_index) const
{
    return _arr[row_index * col_num + col_index];
}

template<typename T, size_t row_num, size_t col_num>
size_t matrix<T, row_num, col_num>::get_row_size() const
{
    return row_num;
}

template<typename T, size_t row_num, size_t col_num>
size_t matrix<T, row_num, col_num>::get_col_size() const
{
    return col_num;
}

template<typename T, size_t row_num, size_t col_num>
size_t matrix<T, row_num, col_num>::get_size() const
{
    return row_num * col_num;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>& matrix<T, row_num, col_num>::operator=(const matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) = other(i, j);
        }
    }
    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>& matrix<T, row_num, col_num>::operator+=(const matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < get_size(); ++i) {
        _arr[i] += other(0, i);
    }
        
    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num>& matrix<T, row_num, col_num>::operator-=(const matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < get_size(); ++i)  {
        _arr[i] -= other(0, i); 
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
template <size_t res_col_num>
matrix<T, row_num, res_col_num> matrix<T, row_num, col_num>::operator*(const matrix<T, col_num, res_col_num>& other) const
{
    matrix<T, row_num, res_col_num> prod;

    for(size_t i = 0; i < row_num; ++i) {
        for(size_t j = 0; j < res_col_num; ++j) {
            for(size_t k = 0; k < col_num; k++) {
                prod(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
     
    return prod;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::hadamard_prod(const matrix<T, row_num, col_num>& other) const
{
    auto had_prod = matrix<T, row_num, col_num>(*this);

    for (size_t i = 0; i < get_size(); ++i) {
        had_prod(0, i) *= other(0, i); 
    }


    return had_prod;  
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator+(const matrix<T, row_num, col_num>& other) const
{
    matrix sum = matrix<T, row_num, col_num>(*this);

    sum += other;

    return sum;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator-(const matrix<T, row_num, col_num>& other) const
{
    matrix sub = matrix<T, row_num, col_num>(*this);

    sub -= other;

    return sub;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator*=(const T& arg)
{
    for(size_t i = 0; i < row_num * col_num; ++i) {
        _arr[i] *= arg;
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator*(const T& arg) const
{
    matrix prod = matrix<T, row_num, col_num>(*this);

    prod *= arg;

    return prod;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, col_num, row_num> matrix<T, row_num, col_num>::get_transp() const
{
    matrix<T, col_num, row_num> transp;

    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            transp(j, i) = (*this)(i, j);
        }
    }

    return transp;
}

template<typename T, size_t row_num, size_t col_num>
template<size_t begin_col, size_t end_col, size_t begin_row, size_t end_row>
matrix<T, end_row - begin_row, end_col - begin_col> matrix<T, row_num, col_num>::slice() const
{
    matrix<T, end_row - begin_row, end_col - begin_col> new_mat;
    size_t k = 0;

    for(size_t i = begin_row; i < end_row; ++i) {
        for(size_t j = begin_col; j < end_col; ++j) {
            new_mat(0, k) = (*this)(i, j);
            ++k;
        }
    }
    return new_mat;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator+=(const T& arg)
{
    for(size_t i = 0; i < row_num * col_num; ++i) {
        _arr[i] += arg;
    }
    
    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator+(const T& arg) const
{
    matrix sum = matrix<T, row_num, col_num>(*this);

    sum += arg;

    return sum;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator-=(const T& arg)
{
    for(size_t i = 0; i < row_num * col_num; ++i) {
        _arr[i] -= arg;
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::operator-(const T& arg) const
{
    matrix sub = matrix<T, row_num, col_num>(*this);

    sub -= arg;
    
    return sub;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> operator*(const T& arg, const matrix<T, row_num, col_num>& other)
{
    matrix<T, row_num, col_num> prod = matrix<T, row_num, col_num>(other);

    prod *= arg;

    return prod;
}

template<typename T, size_t row_num, size_t col_num>
vector_row<T, col_num>  matrix<T, row_num, col_num>::get_row(size_t index) const
{
    matrix<T, 1, col_num> row;

    for(size_t i = 0; i < row_num; ++i) {
        row(0, i) = (*this)(index, i);
    }

    return row;
}

template<typename T, size_t row_num, size_t col_num>
vector_col<T, row_num> matrix<T, row_num, col_num>::get_col(size_t index) const
{
    matrix<T, row_num, 1> col;

    for(size_t i = 0; i < row_num; ++i) {
        col(0, i) = (*this)(i, index);
    }

    return col;
}

template<typename T, size_t row_num, size_t col_num>
vector_row<T, col_num>  matrix<T, row_num, col_num>::get_main_diagonal() const
{
    static_assert(row_num == col_num, "Matrix is not square!");

    matrix<T, 1, col_num> diag;

    for(size_t i = 0; i < row_num; ++i) {
        diag(0, i) = (*this)(i, i);
    }

    return diag;
}

template<typename T, size_t row_num, size_t col_num>
vector_row<T, col_num>  matrix<T, row_num, col_num>::get_secondary_diagonal() const
{
    static_assert(row_num == col_num, "Matrix is not square!");

    matrix<T, 1, col_num> diag;

    for(size_t i = 0; i < row_num; ++i) {
        diag(0, i) = (*this)(i, row_num - 1 - i);
    }

    return diag;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::sum_to_each_row(const vector_row<T, col_num>& vec)
{ 
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) += vec(0, j);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::sum_to_each_col(const vector_col<T, row_num>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) += vec(0, i);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::sub_to_each_row(const vector_row<T, col_num>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) -= vec(0, j);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::sub_to_each_col(const vector_col<T, row_num>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            (*this)(i, j) -= vec(0, i);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num - 1, col_num - 1> get_minor(const matrix<T, row_num, col_num>& mat, size_t row, size_t col)
{
    matrix<T, row_num - 1, col_num - 1> minor;

    for (size_t mat_i = 0, minor_i = 0; mat_i < row_num; ++mat_i) {
        if (mat_i != row) {
            for (size_t mat_j = 0, minor_j = 0; mat_j < col_num; ++mat_j) {
                if (mat_j != col) {
                    minor(minor_i, minor_j) = mat(mat_i, mat_j);

                    ++minor_j;
                }                
            }

            ++minor_i;
        }
    }

    return minor;
}

template<typename T, size_t row_num, size_t col_num>
T matrix<T, row_num, col_num>::get_determinant() const
{
    static_assert(row_num == col_num, "Matrix is not square!");

    if (row_num == 1) {
        return _arr[0];
    } else if (row_num == 2) {
        return _arr[0] * _arr[3] - _arr[1] * _arr[2];
    } else {
        T determinant = 0;

        for (size_t k = 0; k < row_num; k++) {
            auto minor = get_minor(*this, 0, k); // matrix<T, row_num - 1, col_num - 1>

            determinant += ((-1) * (k % 2)) * _arr[k] * minor.get_determinant();
        }

        return determinant;
    }
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> algebraic_complement(const matrix<T, row_num, col_num> mat)
{
    matrix<T, row_num, col_num> result_mat;

    for(size_t i = 0; i < row_num; ++i) {
        for(size_t j = 0; j < col_num; ++i) {
            auto minor = get_minor(mat, i, j);

            result_mat(i, j) = ((-1) * ((i + j) % 2)) * minor.get_determinant();
        }
    }

    return result_mat;
}

template<typename T, size_t row_num, size_t col_num>
matrix<T, row_num, col_num> matrix<T, row_num, col_num>::get_inverse() const
{
    static_assert(row_num == col_num, "Matrix is not square!");
    auto determinant = get_determinant();
    assert(determinant != 0 && "Matrix has no inverse!");

    auto transp_mat = get_transp(); // matrix<T, col_num, row_num> 

    auto transp_mat_alg_comp = algebraic_complement(transp_mat); // matrix<T, col_num, row_num> 

    auto inverse_mat = transp_mat_alg_comp * determinant; // matrix<T, col_num, row_num> 

    return inverse_mat;
}
