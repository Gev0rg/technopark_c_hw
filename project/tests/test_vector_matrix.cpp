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

TEST(vector_matrix, operator_mul_T)
{
    vector_matrix<double, 2, 3> vm {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    vm *= 10;
    EXPECT_DOUBLE_EQ(double(11), vm[0]);
    EXPECT_DOUBLE_EQ(double(22), vm[1]);
    EXPECT_DOUBLE_EQ(double(33), vm[2]);
    EXPECT_DOUBLE_EQ(double(44), vm[3]);
    EXPECT_DOUBLE_EQ(double(55), vm[4]);
    EXPECT_DOUBLE_EQ(double(66), vm[5]);
}

// TEST(vector_matrix, operator_mul_T)
// {
//     vector_matrix<double, 2, 3> vm {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
//     vm *= 10;
//     EXPECT_DOUBLE_EQ(double(11), vm[0]);
//     EXPECT_DOUBLE_EQ(double(22), vm[1]);
//     EXPECT_DOUBLE_EQ(double(33), vm[2]);
//     EXPECT_DOUBLE_EQ(double(44), vm[3]);
//     EXPECT_DOUBLE_EQ(double(55), vm[4]);
//     EXPECT_DOUBLE_EQ(double(66), vm[5]);
// }

// TEST(vector_matrix, mul)
// {
//     vector_matrix<double, 2, 3> vm1 {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
//     vector_matrix<double, 3, 2> vm2 {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
//     vector_matrix<double, 2, 2> vm = vm1.mul(vm2);
//     EXPECT_DOUBLE_EQ(double(26.62), vm[0]);
//     EXPECT_DOUBLE_EQ(double(33.88), vm[1]);
//     EXPECT_DOUBLE_EQ(double(59.29), vm[2]);
//     EXPECT_DOUBLE_EQ(double(77.44), vm[3]);
// }