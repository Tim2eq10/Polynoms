#include <gtest.h>

#include "polynom.h"

TEST(Validity, Polynom) {
	ASSERT_TRUE(true);
	
}

TEST(Polynom_Monome_, getters_) {
	polynom<double>::Monom a(1, 2, 3, 4);
	ASSERT_EQ(a.c, 1);
	ASSERT_EQ(a.xpow(), 2);
	ASSERT_EQ(a.ypow(), 3);
	ASSERT_EQ(a.zpow(), 4);
}

TEST(Polynom_Monome_, equal_and_non_equal) {
	polynom<double>::Monom a(1, 1, 1, 1);
	polynom<double>::Monom b(1, 1, 1, 1);
	polynom<double>::Monom c(1, 2, 1, 1);
	polynom<double>::Monom d(2, 1, 1, 1);
	
	ASSERT_EQ(a, b);
	ASSERT_EQ(a, d);
	
	ASSERT_NE(a, c);
	ASSERT_NE(c, d);
}

//TEST(Polynom_, can_create_empty_polynom_) {
//	ASSERT_NO_THROW(Polynom<double> x);
//}
//
//TEST(Polynom_, empty_pol_is_zero_) {
//
//}
//
//TEST(Polynom_, can_create_polynom_from_vector_) {
//	std::vector<double> a{ 1.0, 2.0, 3.0 };
//	ASSERT_NO_THROW(Polynom<double> x(a));
//}
//
//TEST(Polynom_, can_create_polynom_from_init_list_) {
//	ASSERT_NO_THROW(Polynom<double> x{ 1.0, 2.0, 3.0 });
//}
