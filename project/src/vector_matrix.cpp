#include <vector_matrix.hpp>


template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix()
{
    
}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix(std::initializer_list<T> list)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>::vector_matrix(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator=(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator+=(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator-=(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator*=(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M>& vector_matrix<T, N, M>::operator/=(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator+(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator-(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator*(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator/(const vector_matrix& other)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::operator*(T arg)
{

}

template<typename T, size_t N, size_t M>
T vector_matrix<T, N, M>::operator[](size_t index)
{

}

template<typename T, size_t N, size_t M>
vector_matrix<T, N, M> vector_matrix<T, N, M>::slice(size_t begin, size_t end)
{

}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::line_size()
{
    return this->line_size;
}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::col_size()
{
    return this->col_size;
}

template<typename T, size_t N, size_t M>
size_t vector_matrix<T, N, M>::size()
{
    return this->size();
}

template<typename T, size_t N, size_t M>
std::vector<T> vector_matrix<T, N, M>::arr()
{

}
