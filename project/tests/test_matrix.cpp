#include <gtest/gtest.h>

#include <matrix.hpp>

#include <../src/matrix.cpp>

// TEST(matrix, determinant) 
// {
//     matrix<double, 3, 3> vm = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
//     EXPECT_DOUBLE_EQ(double(0), vm.determinant());
// }

// TEST(matrix, inverse)
// {
//     matrix<double, 3, 3> vm = {2.0, 0.0, -1.0, 1.0, 5.0, -4.0, -1.0, 1.0, 0.0};
//     vm = vm.inverse();
//     EXPECT_DOUBLE_EQ(2.0, vm[0]);
//     EXPECT_DOUBLE_EQ(-0.5, vm[0]);
//     EXPECT_DOUBLE_EQ(2.5, vm[0]);
//     EXPECT_DOUBLE_EQ(2, vm[0]);
//     EXPECT_DOUBLE_EQ(-0.5, vm[0]);
//     EXPECT_DOUBLE_EQ(3.5, vm[0]);
//     EXPECT_DOUBLE_EQ(3, vm[0]);
//     EXPECT_DOUBLE_EQ(-1, vm[0]);
//     EXPECT_DOUBLE_EQ(5, vm[0]);
// }