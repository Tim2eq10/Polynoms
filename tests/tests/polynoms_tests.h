#include "gtest/gtest.h"

#include "include/polynoms/Polynom.h"

#ifndef POLYNOMS_TESTS_H
#define POLYNOMS_TESTS_H

TEST( _Monom, _empty_monom_is_zero ) {
    Monom a;
    Monom b(0);
    ASSERT_EQ(a, b);
}

TEST( _Monom, _constructor ) {
    Monom a(3, 2, 3, 1);
    ASSERT_EQ(a.coef, 3);
    ASSERT_EQ(a.xpower(), 2);
    ASSERT_EQ(a.ypower(), 3);
    ASSERT_EQ(a.zpower(), 1);
    Monom b(3.);
    ASSERT_EQ(b, 3.);
}

TEST( _Monom, _parsing ) {
    Monom a("4x^2y^3z^1");
    Monom b(4, 2, 3, 1);
    ASSERT_EQ(a, b);
    b.coef = 2;
    ASSERT_NE(a, b);
    Monom c("xy");
    ASSERT_EQ(c.xpower(), 1);
    ASSERT_EQ(c.ypower(), 1);
    ASSERT_EQ(c.zpower(), 0);
    ASSERT_EQ(c.coef, 1);

    ASSERT_ANY_THROW(Monom("4x^y^3z^1"));
    ASSERT_ANY_THROW(Monom(";al,flse,/"));
    ASSERT_ANY_THROW(Monom("al"));
}

TEST( _Monom, _assign ) {
    Monom a("4x^2y^3z^1");
    Monom b("4x^2y^3z^1");
    Monom c("4x^2y^3z^1");
    ASSERT_EQ(a, b);
    a = b;
    ASSERT_EQ(a, c);
    ASSERT_EQ(b, c);
}

TEST( _Monom, _binary_operator_plus ) {
    Monom a("3x^2y^3z^1");
    Monom b("1x^2y^3z^1");
    Monom c("4x^2y^3z^1");
    Monom d("x");
    ASSERT_EQ(a + b, c);
    ASSERT_ANY_THROW(a + d);
}

TEST( _Monom, _binary_operator_mult ) {
    Monom a("3xyz");
    Monom b("2x^2y^3z^1");
    Monom c("6x^3y^4z^2");
    Monom d("x^9");
    ASSERT_EQ(a * b, c);
    ASSERT_ANY_THROW(c * d);
}

TEST( _Monom, _binary_operator_minus ) {
    Monom a("3x^2y^3z^1");
    Monom b("-1x^2y^3z^1");
    Monom c("4x^2y^3z^1");
    Monom d("x");
    ASSERT_EQ(a - b, c);
    ASSERT_ANY_THROW(a - d);
}

TEST( _Monom, _value_in_point ) {
    Monom a("3x^2y^3z^1");
    Monom b("xy");
    Monom c("9x^2yz");
    ASSERT_EQ(a.ValueInPoint(2, 1, 3), 36);
    ASSERT_EQ(b.ValueInPoint(1000, 1000, 0), 1000000);
    ASSERT_EQ(c.ValueInPoint(1, 9, 9), 729);
}

#endif // POLYNOMS_TESTS_H
