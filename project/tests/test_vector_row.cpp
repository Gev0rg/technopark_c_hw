#include <gtest/gtest.h>

#include <vector_row.hpp>

TEST(vector_row, parenthesis_operator) {
    vector_row<double, 4> row = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(row(1), 2.2);
}

TEST(vector_row, slice) 
{
    vector_row<double, 9> row1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    auto row2 = row1.slice<0, 4>();
    vector_row<double, 4> result = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(row2 == result);
}
