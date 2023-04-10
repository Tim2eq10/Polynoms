#include <gtest/gtest.h>

#include "tables_tests.h"
#include "polynoms_tests.h"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
