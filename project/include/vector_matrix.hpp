#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

template <typename T, size_t row_num, size_t col_num>
class vector_matrix 
{

public:

    vector_matrix() = default;
    template<typename... Type>
    vector_matrix(Type...); // заменил инит лист на это, но как контролировать размер
    vector_matrix(const vector_matrix&);
    vector_matrix(const vector_matrix<T, 1, col_num>&); // глянуть сюда
    vector_matrix(const vector_matrix<T, row_num, 1>&);
    vector_matrix& operator=(const vector_matrix&);

    vector_matrix& operator+=(const vector_matrix&);
    vector_matrix& operator-=(const vector_matrix&);    

    vector_matrix operator+(const vector_matrix&) const;
    vector_matrix operator-(const vector_matrix&) const;
    vector_matrix hadamard_prod(const vector_matrix&); // поэлементное умножение
    
    template <size_t res_col_num>
    vector_matrix<T, row_num, res_col_num> operator*(const vector_matrix<T, col_num, res_col_num>&) const;
    // обычное произведение, так понимаю, работет только с копией, потому что поментять _arr мы не можем

    vector_matrix operator+=(const T&);
    vector_matrix operator-=(const T&);
    vector_matrix operator*=(const T&);

    vector_matrix operator+(const T&) const;
    vector_matrix operator-(const T&) const;
    vector_matrix operator*(const T&) const;

    T& operator()(size_t, size_t);

    template <size_t begin_col, size_t end_col, size_t begin_row = 0, size_t end_row = 1>
    vector_matrix<T, end_row - begin_row, end_col - begin_col> slice() const; 
    // а как вместо передачи через шаблон передать через функцию, там с constexpr траблы же

    vector_matrix<T, col_num, row_num> get_transp() const;

    size_t get_row_size() const;
    size_t get_col_size() const;
    size_t get_size() const;

    std::array<T, row_num * col_num>& arr() const; // хз, мб оставить, я его в конструкторе использую

    vector_matrix<T, 1, col_num> get_row(size_t); // глянуть сюда
    vector_matrix<T, row_num, 1> get_col(size_t);

    vector_matrix<T, 1, col_num> get_main_diagonal();
    vector_matrix<T, 1, col_num> get_secondary_diagonal();

    vector_matrix sum_to_each_row(const vector_matrix<T, 1, col_num>&);
    vector_matrix sum_to_each_col(const vector_matrix<T, row_num, 1>&);
    vector_matrix sub_to_each_row(const vector_matrix<T, 1, col_num>&);
    vector_matrix sub_to_each_col(const vector_matrix<T, row_num, 1>&);
    
    T get_determinant();
    vector_matrix get_inverse();

    bool is_square(); // или же мне писать в <> что-то типа row_num, row_num и забить на этот метод

private:

    std::array<T, row_num * col_num> _arr; // можно ли просто сделать массив публичным и не париться с arr()
    
};

template<typename T, size_t row_num, size_t col_num>
template<typename... Type>
vector_matrix<T, row_num, col_num>::vector_matrix(Type... init_list) : _arr{ { init_list... } } { }

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>::vector_matrix(const vector_matrix& other) : _arr(other.arr()) { }

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>::vector_matrix(const vector_matrix<T, 1, col_num>& vec)
{
    size_t iter = 0;
    for (size_t i = 0; i < row_num; ++i) {
        std::copy(vec.arr().begin(), vec.arr().end(), _arr.begin() + iter); // так сработает? если да, то мне оставить arr()?
        iter += col_num;
    }
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>::vector_matrix(const vector_matrix<T, row_num, 1>& vec)
{
    size_t arr_index = 0;
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            _arr[arr_index++] = vec(0, i);
        }
    }
}

template<typename T, size_t row_num, size_t col_num>
bool vector_matrix<T, row_num, col_num>::is_square() 
{
    return row_num == col_num;
}

template<typename T, size_t row_num, size_t col_num>
T& vector_matrix<T, row_num, col_num>::operator()(size_t row_index, size_t col_index) 
{
    return _arr[row_index * col_num + col_index];
}

template<typename T, size_t row_num, size_t col_num>
size_t vector_matrix<T, row_num, col_num>::get_row_size() const
{
    return row_num;
}

template<typename T, size_t row_num, size_t col_num>
size_t vector_matrix<T, row_num, col_num>::get_col_size() const
{
    return col_num;
}

template<typename T, size_t row_num, size_t col_num>
size_t vector_matrix<T, row_num, col_num>::get_size() const
{
    return row_num * col_num;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>& vector_matrix<T, row_num, col_num>::operator=(const vector_matrix<T, row_num, col_num>& other)
{
    _arr = other.arr();
    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>& vector_matrix<T, row_num, col_num>::operator+=(const vector_matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < get_size(); ++i) 
        _arr[i] += other[i];
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num>& vector_matrix<T, row_num, col_num>::operator-=(const vector_matrix<T, row_num, col_num>& other)
{
    for (size_t i = 0; i < get_size(); ++i) 
        _arr[i] -= other[i]; 
}

template<typename T, size_t row_num, size_t col_num>
template <size_t res_col_num>
vector_matrix<T, row_num, res_col_num> vector_matrix<T, row_num, col_num>::operator*(const vector_matrix<T, col_num, res_col_num>& other) const
{
    vector_matrix<T, row_num, res_col_num> prod;

    for(size_t i = 0; i < row_num; ++i) {
        for(size_t j = 0; j < res_col_num; ++j) {
            for(size_t k = 0; k < col_num; k++) {
                prod(i, j) += *this(i, k) * other(k, j);
            }
        }
    }
     
    return prod;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::hadamard_prod(const vector_matrix<T, row_num, col_num>& other)
{
    auto had_prod = vector_matrix<T, row_num, col_num>(*this);

    for (size_t i = 0; i < get_size(); ++i) 
        had_prod[i] *= other[i]; 

    return had_prod;  
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator+(const vector_matrix<T, row_num, col_num>& other) const
{
    vector_matrix sum = vector_matrix<T, row_num, col_num>(*this);

    sum += other;

    return sum;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator-(const vector_matrix<T, row_num, col_num>& other) const
{
    vector_matrix sub = vector_matrix<T, row_num, col_num>(*this);

    sub -= other;

    return sub;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator*=(const T& arg)
{
    for(auto a : _arr)
        a *= arg;

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator*(const T& arg) const
{
    vector_matrix prod = vector_matrix<T, row_num, col_num>(*this);

    prod *= arg;

    return prod;
}

template<typename T, size_t row_num, size_t col_num>
std::array<T, row_num * col_num>& vector_matrix<T, row_num, col_num>::arr() const
{
    return _arr;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, col_num, row_num> vector_matrix<T, row_num, col_num>::get_transp() const
{
    vector_matrix<T, col_num, row_num> transp;

    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            transp(j, i) = *this(i, j);
        }
    }

    return transp;
}

template<typename T, size_t row_num, size_t col_num>
template<size_t begin_col, size_t end_col, size_t begin_row, size_t end_row>
vector_matrix<T, end_row - begin_row, end_col - begin_col> vector_matrix<T, row_num, col_num>::slice() const
{
    vector_matrix<T, end_row - begin_row, end_col - begin_col> new_mat;
    size_t k = 0;

    for(size_t i = begin_row; i < end_row; ++i)
    {
        for(size_t j = begin_col; j < end_col; ++j) 
        {
            new_mat.arr()[k] = _arr[i * col_num + j]; // как здесь этот ужас норм сделать
            ++k;
        }
    }
    return new_mat;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator+=(const T& arg)
{
    for(auto a : _arr)
        a += arg;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator+(const T& arg) const
{
    vector_matrix sum = vector_matrix<T, row_num, col_num>(*this);

    for(auto a : sum.arr())
        a += arg;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator-=(const T& arg)
{
    for(auto a : _arr)
        a -= arg;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::operator-(const T& arg) const
{
    vector_matrix sub = vector_matrix<T, row_num, col_num>(*this);

    for(auto a : sub.arr())
        a -= arg;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> operator*(const T& arg, const vector_matrix<T, row_num, col_num>& other)
{
    vector_matrix<T, row_num, col_num> prod = vector_matrix<T, row_num, col_num>(other);

    prod *= arg;

    return prod;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, 1, col_num> vector_matrix<T, row_num, col_num>::get_row(size_t index)
{
    vector_matrix<T, 1, col_num> row;

    std::copy(_arr.begin() + index * col_num, _arr.begin() + (index + 1) * col_num, row.arr().begin()); // сработает ли

    return row;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, 1> vector_matrix<T, row_num, col_num>::get_col(size_t index)
{
    vector_matrix<T, row_num, 1> col;

    for(size_t i = 0; i < row_num; ++i) {
        col(0, i) = *this(i, index);
    }

    return col;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, 1, col_num> vector_matrix<T, row_num, col_num>::get_main_diagonal()
{
    static_assert(is_square(), "Matrix is not square!");

    vector_matrix<T, 1, col_num> diag;

    for(size_t i = 0; i < row_num; ++i) {
        diag[i] = *this(i, i);
    }

    return diag;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, 1, col_num> vector_matrix<T, row_num, col_num>::get_secondary_diagonal()
{
    static_assert(is_square(), "Matrix is not square!");

    vector_matrix<T, 1, col_num> diag;

    for(size_t i = 0; i < row_num; ++i) {
        diag[i] = *this(row_num - i, row_num - i);
    }

    return diag;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::sum_to_each_row(const vector_matrix<T, 1, col_num>& vec)
{ 
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            *this(i, j) += vec(0, j);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::sum_to_each_col(const vector_matrix<T, row_num, 1>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            *this(i, j) += vec(0, i);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::sub_to_each_row(const vector_matrix<T, 1, col_num>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            *this(i, j) -= vec(0, j);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::sub_to_each_col(const vector_matrix<T, row_num, 1>& vec)
{
    for (size_t i = 0; i < row_num; ++i) {
        for (size_t j = 0; j < col_num; ++j) {
            *this(i, j) -= vec(0, i);
        }
    }

    return *this;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num - 1, col_num - 1> get_minor(vector_matrix<T, row_num, col_num>& mat, size_t row, size_t col)
{
    vector_matrix<T, row_num - 1, col_num - 1> minor;

    for (size_t mat_i = 0, minor_i = 0; mat_i < row_num; ++mat_i) {
        if (mat_i != row)
        {
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
T vector_matrix<T, row_num, col_num>::get_determinant()
{
    static_assert(is_square(), "Matrix is not square!");

    if (row_num == 1) {
        return _arr[0];
    } else if (row_num == 2) {
        return _arr[0] * _arr[3] - _arr[1] * _arr[2];
    } else {
        T determinant = 0;

        for (size_t k = 0; k < row_num; k++) {
            vector_matrix<T, row_num - 1, col_num - 1> minor = get_minor(*this, 1, k); // здесь auto ипользовать типа

            determinant += ((-1) * (k % 2)) * _arr[k] * minor.get_determinant();
        }

        return determinant;
    }
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> algebraic_complement(vector_matrix<T, row_num, col_num> mat)
{
    vector_matrix<T, row_num, col_num> result_mat;

    for(size_t i = 0; i < row_num; ++i)
    {
        for(size_t j = 0; j < col_num; ++i)
        {
            result_mat(i, j) = ((-1) * (i + j) % 2) * get_minor(mat, i, j);
        }
    }

    return result_mat;
}

template<typename T, size_t row_num, size_t col_num>
vector_matrix<T, row_num, col_num> vector_matrix<T, row_num, col_num>::get_inverse()
{
    static_assert(is_square(), "Matrix is not square!");
    constexpr size_t determinant = get_determinant();
    static_assert(determinant != 0, "Matrix has no inverse!");

    vector_matrix<T, col_num, row_num> transp_mat = get_transp(); // здесь auto ипользовать типа

    vector_matrix<T, col_num, row_num> transp_mat_alg_comp = algebraic_complement(transp_mat); // здесь auto ипользовать типа

    vector_matrix<T, col_num, row_num> inverse_mat = transp_mat_alg_comp * determinant; // здесь auto ипользовать типа

    return inverse_mat;
}