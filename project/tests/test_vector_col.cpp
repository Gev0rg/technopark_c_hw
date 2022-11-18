#include <gtest/gtest.h>

#include <vector_col.hpp>

TEST(vector_col, parenthesis_operator) {
    vector_col<double, 4> col = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_EQ(col(1), 2.2);
}

TEST(vector_col, slice) 
{
    vector_col<double, 9> col1 = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    auto col2 = col1.slice<0, 4>();
    vector_col<double, 4> result = { 1.1, 2.2, 3.3, 4.4 };
    EXPECT_TRUE(col2 == result);
}
