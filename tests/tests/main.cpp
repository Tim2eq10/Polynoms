#include "include/tables/unsorted_array.h"
#include <gtest/gtest.h>

TEST( test001, _Validity ) {
    ASSERT_TRUE(true);
}

TEST( test002, insertion ) {
    _Table_unsorted_array<int, int> a;
    ASSERT_EQ(0, a.size());
    a.insert(1, 1);
    assert(a.size() == 1);
    a.insert(2, 1);
    assert(a.size() == 2);
    a.insert(3, 1);
    assert(a.size() == 3);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
