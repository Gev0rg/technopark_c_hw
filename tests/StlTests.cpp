#include <gtest/gtest.h>

#include <set>
#include <sstream>
#include <vector>

#include "Iterator.hpp"
#include "Stl.hpp"

// template <typename T, typename Comparator>
// void TestInsertErase(Stl<T, Comparator> &set, std::istream &in) {
//     char op;
//     T data;
//     while (in >> op >> data) {
//         switch (op) {
//             case '+': {
//                 set.insert(data);
//                 break;
//             }
//             case '-': {
//                 set.erase(data);
//                 break;
//             }
//         }
//     }
// }

// TEST(TestBasicsFunctional, Test_Insert_Erase_Find_LowerBound) { // 1
//     Stl<int> set;
//     EXPECT_EQ(set.size(), 0);
//     EXPECT_TRUE(set.empty());

//     // fill 1..9, -20, 20
//     // remove odd
//     std::string strTest = "+ 1 + 1 + 2 + 2 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 - 2 - 4 - 6 - 8 -8 -8 + -20 + 20";
//     std::istringstream stream(strTest);
//     TestInsertErase(set, stream);

//     EXPECT_EQ(set.size(), 7);
//     EXPECT_TRUE(!set.empty());

//     EXPECT_EQ(*(set.find(1)), 1);
//     EXPECT_EQ(*(set.find(3)), 3);
//     EXPECT_EQ(*(set.find(5)), 5);
//     EXPECT_EQ(*(set.find(7)), 7);
//     EXPECT_EQ(*(set.find(9)), 9);
//     EXPECT_EQ(*(set.find(-20)), -20);
//     EXPECT_EQ(*(set.find(20)), 20);

//     EXPECT_EQ(*(set.lower_bound(2)), 3);
//     EXPECT_EQ(*(set.lower_bound(9)), 9);
//     EXPECT_EQ(*(set.lower_bound(-100)), -20);

//     // EXPECT_EQ: отсутствие оператора == ...
//     EXPECT_TRUE(set.find(2) == set.end());
//     EXPECT_TRUE(set.find(4) == set.end());
//     EXPECT_TRUE(set.find(6) == set.end());
//     EXPECT_TRUE(set.find(8) == set.end());

//     set.erase(12345);
//     for (auto elem : {1, 3, 5, 7, 9, -20}) {
//         set.erase(elem);
//     }
//     EXPECT_EQ(set.size(), 1);
//     set.erase(20);
//     EXPECT_EQ(set.size(), 0);
//     set.erase(20);
//     set.erase(2001);
// }

// TEST(TestBasicsFunctional, Test_Increment_Decrement_Begin_End) { // 2
//     Stl<int> set;
//     EXPECT_TRUE(set.begin() == set.end());
//     set = {10, 20, 30, 40, 50, 60, 70, 80, 90};
//     Stl<int>::iterator it = set.find(40);
//     EXPECT_TRUE(it != set.end());
//     EXPECT_EQ(*it, 40);
//     EXPECT_EQ(*(--it), 30);
//     EXPECT_EQ(*(it++), 30);
//     EXPECT_EQ(*(it), 40);
//     EXPECT_EQ(*(++it), 50);
//     EXPECT_TRUE(it == set.find(50));
//     EXPECT_TRUE(it != set.find(70));
//     EXPECT_EQ(*set.begin(), 10);
//     EXPECT_EQ(*(++set.begin()), 20);
//     // РАБОТАЕТ!!!
//     EXPECT_EQ(*(--set.end()), 90);
// }

// struct A {
//     int a;
//     int b;
//     bool operator<(A const &right) const { return a < right.a; }
// };

// TEST(TestBasicsFunctional, Test_Before_Begin) { // 3
//     Stl<A> set;
//     set = {{1, 2}, {3, 4}, {5, 6}};
//     auto it = set.begin();
//     it--;
//     EXPECT_THROW(*it, std::exception);
//     EXPECT_THROW(it->a, std::exception);
//     ++it;
//     EXPECT_EQ(it->b, 2);
// }

// TEST(TestBasicsFunctional, Test_Iterator_default_ctor) { // 4
//     Stl<int> set = {1, 2, 3};
//     Stl<int>::iterator it;
//     it = set.begin();
//     EXPECT_EQ(*it, 1);
// }

// TEST(TestBasicsFunctional, Test_Insert_Erase_Random) { // 5
//     Stl<int> set = {4, 6, 2};
//     set.insert(1);
//     set.insert(3);
//     set.insert(45);
//     set.insert(13);
//     set.insert(78);
//     set.insert(-13);
//     set.insert(-345);
//     set.insert(-6);
//     set.erase(1);
//     set.erase(-13);
//     set.erase(-345);
//     set.erase(2);
//     set.erase(45);
//     set.insert(777);
//     set.erase(78);
//     set.erase(777);
// }

// TEST(TestBasicsFunctional, Test_Ctor_CopyCtor_AssignOperator) { // 6
//     Stl<int> set0 = {1, 2, 3, 4, 5};
//     Stl<int> set1(set0);
//     Stl<int> set2(set1.begin(), set1.end());
//     EXPECT_EQ(set1, set2);
//     set2.erase(4);
//     EXPECT_NE(set1, set2);

//     set2 = set1;
//     EXPECT_EQ(set1, set2);

//     auto it1 = set1.find(2);
//     auto it2 = set1.find(5);
//     Stl<int> set3(it1, it2);
//     EXPECT_EQ(set3.size(), 3);
//     auto it = set3.begin();
//     for (auto elem : {2, 3, 4}) {
//         EXPECT_EQ(*it, elem);
//         ++it;
//     }
// }

TEST(TestBasicsFunctional, Test_Compatibility_with_STL_Next_Advance_Prev) { // 7
    Stl<int> set = {1, 2, 3, 4, 5};
    Stl<int>::iterator it = set.begin();
    std::advance(it, 3);
    EXPECT_EQ(*it, 4);
    auto it2 = std::next(it);
    EXPECT_EQ(*it2, 5);
    it2 = std::prev(it, 2);
    EXPECT_EQ(*it2, 2);
}
