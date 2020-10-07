#include <amylase/polynomial>
#include <atcoder/modint>
#include <gtest/gtest.h>

using li = long long;
using mint = atcoder::modint1000000007;
using intpoly = amylase::polynomial<li>;
using modpoly = amylase::polynomial<mint>;
using floatpoly = amylase::polynomial<double>;

TEST(PolynomialTest, Add) {
    intpoly p({1, 2});
    intpoly q({3, 4, 5});
    intpoly r = p + q;

    ASSERT_EQ(r, intpoly({4, 6, 5}));
}

TEST(PolynomialTest, Subtract) {
    intpoly p({1, 2, 5});
    intpoly q({3, 4, 5});
    intpoly r = p - q;

    ASSERT_EQ(r, intpoly({-2, -2}));
}

TEST(PolynomialTest, Substitute) {
    intpoly p({1, 2, 5});

    ASSERT_EQ(25, p.substitute(2));
}

TEST(PolynomialTest, Derivative) {
    intpoly p({1, 2, 5});

    ASSERT_EQ(p.derivative(), intpoly({2, 10}));
}

TEST(PolynomialTest, ModInt) {
    modpoly p({1, 2});
    modpoly q({3, 4});
    modpoly r = p - q;

    ASSERT_EQ(r, modpoly({1000000005, 1000000005}));
}

TEST(PolynomialTest, Float) {
    floatpoly p({1.5, 2.5});
    floatpoly q({3.5, 4.5});
    floatpoly r = p - q;

    ASSERT_EQ(r, floatpoly({-2, -2}));
}