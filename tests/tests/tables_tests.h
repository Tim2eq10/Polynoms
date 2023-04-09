#include "gtest/gtest.h"

#include "include/tables/connector.h"

#ifndef TABLES_TESTS_H
#define TABLES_TESTS_H

struct Table_test {
    template <typename _Table_class>
    static void insertion_int() {
        _Table_class a;
        ASSERT_EQ(0, a.size());
        a.insert(1, 1);
        ASSERT_EQ(a.size(), 1);
        a.insert(2, 1);
        ASSERT_EQ(a.size(), 2);
        a.insert(3, 1);
        ASSERT_EQ(a.size(), 3);
    }
    template <typename _Table_class>
    static void finding_int() {
        _Table_class a;
        a.insert(1, 1);
        a.insert(2, 1);
        a.insert(3, 1);
        ASSERT_TRUE(a.find(1));
        ASSERT_TRUE(a.find(2));
        ASSERT_TRUE(a.find(3));
        ASSERT_FALSE(a.find(4));
    }
    template <typename _Table_class>
    static void removing_int() {
        _Table_class a;
        a.insert(1, 1);
        a.insert(2, 1);
        a.insert(3, 1);
        a.remove(2);
        ASSERT_EQ(a.size(), 2);
        ASSERT_TRUE(a.find(1));
        ASSERT_TRUE(a.find(3));
        ASSERT_FALSE(a.find(2));
        a.remove(1);
        ASSERT_EQ(a.size(), 1);
        ASSERT_TRUE(a.find(3));
        ASSERT_FALSE(a.find(1));
        a.remove(3);
        ASSERT_TRUE(a.empty());
        ASSERT_FALSE(a.find(1));
    }
    template <typename _Table_class>
    static void at_method_int() {
        _Table_class a;
        a.insert(1, 4);
        a.insert(2, 5);
        a.insert(3, 6);
        ASSERT_EQ(a.at(1), 4);
        ASSERT_EQ(a.at(2), 5);
        ASSERT_EQ(a.at(3), 6);
        ASSERT_ANY_THROW(a.at(4)); //C6031
    }

};


TEST( Tables_, _Validity ) {
    ASSERT_TRUE(true);
}


TEST( _Table_unsorted_array, _Insertion ) {
    Table_test::insertion_int<_Table_unsorted_array<int, int>>();
}
TEST( _Table_unsorted_list, _Insertion ) {
    Table_test::insertion_int<_Table_unsorted_list<int, int>>();
}
TEST( _Table_sorted_array, _Insertion ) {
    Table_test::insertion_int<_Table_sorted_array<int, int>>();
}
TEST( _HashMap_Chains, _Insertion ) {
    Table_test::insertion_int<_HashMap_Chains<int, int>>();
}
TEST( _HashMap_OpenAddressing, _Insertion ) {
    Table_test::insertion_int<_HashMap_OpenAddressing<int, int>>();
}
TEST( _Map_AVL_Tree, _Insertion ) {
    Table_test::insertion_int<_Map_AVL_Tree<int, int>>();
}

TEST( _Table_unsorted_array, _Finding ) {
    Table_test::finding_int<_Table_unsorted_array<int, int>>();
}
TEST( _Table_unsorted_list, _Finding ) {
    Table_test::finding_int<_Table_unsorted_list<int, int>>();
}
TEST( _Table_sorted_array, _Finding ) {
    Table_test::finding_int<_Table_sorted_array<int, int>>();
}
TEST( _HashMap_Chains, _Finding ) {
    Table_test::finding_int<_HashMap_Chains<int, int>>();
}
TEST( _HashMap_OpenAddressing, _Finding ) {
    Table_test::finding_int<_HashMap_OpenAddressing<int, int>>();
}
TEST( _Map_AVL_Tree, _Finding ) {
    Table_test::finding_int<_Map_AVL_Tree<int, int>>();
}

TEST( _Table_unsorted_array, _Removing ) {
    Table_test::removing_int<_Table_unsorted_array<int, int>>();
}
TEST( _Table_unsorted_list, _Removing ) {
    Table_test::removing_int<_Table_unsorted_list<int, int>>();
}
TEST( _Table_sorted_array, _Removing ) {
    Table_test::removing_int<_Table_sorted_array<int, int>>();
}
TEST( _HashMap_Chains, _Removing ) {
    Table_test::removing_int<_HashMap_Chains<int, int>>();
}
TEST( _HashMap_OpenAddressing, _Removing ) {
    Table_test::removing_int<_HashMap_OpenAddressing<int, int>>();
}
TEST( _Map_AVL_Tree, _Removing ) {
    Table_test::removing_int<_Map_AVL_Tree<int, int>>();
}

TEST( _Table_unsorted_array, _At ) {
    Table_test::at_method_int<_Table_unsorted_array<int, int>>();
}
TEST( _Table_unsorted_list, _At ) {
    Table_test::at_method_int<_Table_unsorted_list<int, int>>();
}
TEST( _Table_sorted_array, _At ) {
    Table_test::at_method_int<_Table_sorted_array<int, int>>();
}
TEST( _HashMap_Chains, _At ) {
    Table_test::at_method_int<_HashMap_Chains<int, int>>();
}
TEST( _HashMap_OpenAddressing, _At ) {
    Table_test::at_method_int<_HashMap_OpenAddressing<int, int>>();
}
TEST( _Map_AVL_Tree, _At ) {
    Table_test::at_method_int<_Map_AVL_Tree<int, int>>();
}

#endif // TABLES_TESTS_H
