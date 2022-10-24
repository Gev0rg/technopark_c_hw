#include <gtest/gtest.h>

#include <vector_matrix.hpp>

#include <../src/vector_matrix.cpp>

TEST(vector_matrix, slice) 
{
    vector_matrix<double, 2, 3> vm {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    vector_matrix<double, 1, 2> new_vm = vm.slice<0, 2, 0, 1>();
    EXPECT_DOUBLE_EQ(double(1.1), new_vm[0]);
    EXPECT_DOUBLE_EQ(double(2.2), new_vm[1]);
}