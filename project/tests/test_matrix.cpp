#include "matrix.hpp"
#include "vector_col.hpp"
#include "vector_row.hpp"

#include <gtest/gtest.h>


TEST(matrix, assignment_operator) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    matrix<double, 2, 2> mat2 = mat1;
    EXPECT_TRUE(mat1 == mat2);
}

TEST(matrix, constructor_from_row_vector) {
    vector_row<double, 3> row = { 1.1, 2.2, 3.3 };
    matrix<double, 3, 3> mat2(row);
    matrix<double, 3, 3> result = { 1.1, 2.2, 3.3, 1.1, 2.2, 3.3, 1.1, 2.2, 3.3 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, constructor_from_col_vector) {
    vector_col<double, 3> col = { 1.1, 2.2, 3.3 };
    matrix<double, 3, 3> mat2(col);
    matrix<double, 3, 3> result = { 1.1, 1.1, 1.1, 2.2, 2.2, 2.2, 3.3, 3.3, 3.3 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, init_list) {
    matrix<double, 2, 2> mat = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(mat(0, 1), 2.2);
}

TEST(matrix, parenthesis_operator) {
    matrix<double, 2, 2> mat = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(mat(0, 1), 2.2);
}

TEST(matrix, get_row_size) {
    matrix<double, 2, 2> mat = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(mat.get_row_size(), 2);
}

TEST(matrix, get_col_size) {
    matrix<double, 2, 2> mat = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(mat.get_col_size(), 2);
}

TEST(matrix, get_size) {
    matrix<double, 2, 2> mat = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(mat.get_size(), 4);
}

TEST(matrix, equality_operator) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    matrix<double, 2, 2> mat2 = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(mat1 == mat2);
}

TEST(matrix, copy_constructor) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    matrix<double, 2, 2> mat2(mat1);
    EXPECT_TRUE(mat1 == mat2);
}

TEST(matrix, prod_assignment_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    mat1 *= 2.2;
    matrix<double, 2, 2> result = { 1.1 * 2.2, 2.2 * 2.2, 3.3 * 2.2, 4.4 * 2.2 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, prod_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat2 = mat1 * 2;
    matrix<double, 2, 2> result = { 2.2, 4.4, 6.6, 8.8 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, prod_operator_arg_with_matrix) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat2 = 2.0 * mat1;
    matrix<double, 2, 2> result = { 2.2, 4.4, 6.6, 8.8 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, plus_assignment_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    mat1 += 2.2;
    matrix<double, 2, 2> result = { 1.1 + 2.2, 2.2 + 2.2, 3.3 + 2.2, 4.4 + 2.2 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, plus_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat2 = mat1 + 2.2;
    matrix<double, 2, 2> result = { 1.1 + 2.2, 2.2 + 2.2, 3.3 + 2.2, 4.4 + 2.2 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, minus_assignment_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1 + 2.2, 2.2 + 2.2, 3.3 + 2.2, 4.4 + 2.2 };
    mat1 -= 2.2;
    matrix<double, 2, 2> result = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, minus_operator_with_arg) {
    matrix<double, 2, 2> mat1 = { 1.1 + 2.2, 2.2 + 2.2, 3.3 + 2.2, 4.4 + 2.2 };
    auto mat2 = mat1 - 2.2;
    matrix<double, 2, 2> result = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, plus_assignment_operator_with_matrix) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    matrix<double, 2, 2> mat2 = { 1.1, 2.2, 3.3, 4.4 };
    mat1 += mat2;
    matrix<double, 2, 2> result = { 2.2, 4.4, 6.6, 8.8 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, minus_assignment_operator_with_matrix) {
    matrix<double, 2, 2> mat1 = { 2.2, 4.5, 6.6, 8.8 };
    matrix<double, 2, 2> mat2 = { 1.1, 2.2, 3.3, 4.4 };
    mat1 -= mat2;
    matrix<double, 2, 2> result = { 1.1, 2.3, 3.3, 4.4 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, prod_operator_with_matrix) {
    matrix<double, 2, 2> mat1 = { 2.1, 2.1, 2.1, 2.1 };
    matrix<double, 2, 3> mat2 = { 2.1, 2.1, 2.1, 2.1, 2.1, 2.1 };
    matrix<double, 2, 3> mat3 = { 8.82, 8.82, 8.82, 8.82, 8.82, 8.82 };
    auto result = mat1 * mat2;
    EXPECT_TRUE(result == mat3);
}

TEST(matrix, hadamard_prod) {
    matrix<double, 2, 2> mat1 = { 2.1, 2.1, 2.1, 2.1 };
    matrix<double, 2, 2> mat2 = { 2.1, 2.1, 2.1, 2.1 };
    matrix<double, 2, 2> mat3 = { 4.41, 4.41, 4.41, 4.41 };
    auto result = mat1.hadamard_prod(mat2);
    EXPECT_TRUE(result == mat3);
}

TEST(matrix, plus_operator) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    matrix<double, 2, 2> mat2 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat3 = mat1 + mat2;
    matrix<double, 2, 2> result = { 2.2, 4.4, 6.6, 8.8 };
    EXPECT_TRUE(mat3 == result);
}

TEST(matrix, minus_operator) {
    matrix<double, 2, 2> mat1 = { 2.2, 4.4, 6.6, 8.8 };
    matrix<double, 2, 2> mat2 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat3 = mat1 - mat2;
    matrix<double, 2, 2> result = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(mat3 == result);
}

TEST(matrix, get_transp) {
    matrix<double, 2, 2> mat1 = { 1.1, 2.2, 3.3, 4.4 };
    auto mat2 = mat1.get_transp();
    matrix<double, 2, 2> result = { 1.1, 3.3, 2.2, 4.4 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, slice) 
{
    matrix<double, 3, 3> mat1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    auto mat2 = mat1.slice<0, 2, 0, 2>();
    matrix<double, 2, 2> result = { 1.1, 2.2, 4.4, 5.5 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, get_row) 
{
    matrix<double, 3, 3> mat1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    vector_row<double, 3> row = mat1.get_row(2);
    vector_row<double, 3> result = { 7.7, 8.8, 9.9 };
    EXPECT_TRUE(row == result);
}

TEST(matrix, get_col) 
{
    matrix<double, 3, 3> mat1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    vector_col<double, 3> col = mat1.get_col(1);
    vector_col<double, 3> result = { 2.2, 5.5, 8.8 };
    EXPECT_TRUE(col == result);
}

TEST(matrix, get_main_diagonal) 
{
    matrix<double, 3, 3> mat1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    vector_row<double, 3> diag = mat1.get_main_diagonal();
    vector_row<double, 3> result = { 1.1, 5.5, 9.9 };
    EXPECT_TRUE(diag == result);
}

TEST(matrix, get_secondary_diagonal) 
{
    matrix<double, 3, 3> mat1 = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    vector_row<double, 3> diag = mat1.get_secondary_diagonal();
    vector_row<double, 3> result = { 3.3, 5.5, 7.7 };
    EXPECT_TRUE(diag == result);
}

TEST(matrix, sum_to_each_row) 
{
    matrix<double, 3, 3> mat1 = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1.1 };
    vector_row<double, 3> row = { 1.1, 1.1, 1.1 };
    mat1.sum_to_each_row(row);
    matrix<double, 3, 3> result = { 1.1 + 1.1, 2.2 + 1.1, 3.3 + 1.1, 4.4 + 1.1, 
                                            5.5 + 1.1, 6.6 + 1.1, 7.7 + 1.1, 8.8 + 1.1, 1.1 + 1.1 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, sum_to_each_col) 
{
    matrix<double, 3, 3> mat1 = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1.1 };
    vector_col<double, 3> col = { 1.1, 1.1, 1.1 };
    mat1.sum_to_each_col(col);
    matrix<double, 3, 3> result = { 1.1 + 1.1, 2.2 + 1.1, 3.3 + 1.1, 4.4 + 1.1, 
                                            5.5 + 1.1, 6.6 + 1.1, 7.7 + 1.1, 8.8 + 1.1, 1.1 + 1.1 };
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, sub_to_each_row) 
{
    matrix<double, 3, 3> mat1 = { 1.1 + 1.1, 2.2 + 1.1, 3.3 + 1.1, 4.4 + 1.1, 
                                        5.5 + 1.1, 6.6 + 1.1, 7.7 + 1.1, 8.8 + 1.1, 1.1 + 1.1 };
    vector_row<double, 3> row = { 1.1, 1.1, 1.1 };
    mat1.sub_to_each_row(row);
    matrix<double, 3, 3> result = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1.1 };
    mat1.print();
    result.print();
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, sub_to_each_col) 
{
    matrix<double, 3, 3> mat1 = { 1.1 + 1.1, 2.2 + 1.1, 3.3 + 1.1, 4.4 + 1.1, 
                                        5.5 + 1.1, 6.6 + 1.1, 7.7 + 1.1, 8.8 + 1.1, 1.1 + 1.1 };
    vector_col<double, 3> col = { 1.1, 1.1, 1.1 };
    mat1.sub_to_each_col(col);
    matrix<double, 3, 3> result = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 1.1 };
    mat1.print();
    result.print();
    EXPECT_TRUE(mat1 == result);
}

TEST(matrix, get_minor) 
{
    matrix<double, 3, 3> mat1 = { 2.2, 3.3, 4.4, 
                                  5.5, 6.6, 7.7, 
                                  8.8, 9.9, 2.2 };
    matrix<double, 2, 2> mat2 = get_minor(mat1, 0, 0);
    matrix<double, 2, 2> result = { 6.6, 7.7, 9.9, 2.2 };
    EXPECT_TRUE(mat2 == result);
}

TEST(matrix, get_determinant) 
{
    matrix<double, 3, 3> mat1 = { 11.2, 10.2, 6.2, 
                                  5.2, 9.2, 8.4, 
                                  4.2, 3.2, 2.2 };
    EXPECT_EQ(mat1.get_determinant(), 162/5);
}

TEST(matrix, get_inverse) 
{
    matrix<double, 3, 3> mat1 = { 1.0, 2.0, 3.0, 4.0, 11.0, 6.0, 7.0, 8.0, 9.0};
    matrix<double, 3, 3> mat2 = mat1.get_inverse();
    matrix<double, 3, 3> result = { -17/24.0 , -1/12.0, 7/24.0, -1/12.0, 1/6.0, -1/12.0, 0.625, -1/12.0, -1/24.0};
    EXPECT_TRUE(mat2 == result);
}
