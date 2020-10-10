#include <gtest/gtest.h>

#include "../utils/math.hpp"
#include <numeric>

TEST(UtilsMathTest, FactorsTest) {
    for (int m = 1; m <= 50000; m++) {
        auto f = factors(m);
        int m2 = m;
        for (auto x : f) {
            ASSERT_EQ(0, m % x);
            while (m2 % x == 0) m2 /= x;
        }
        ASSERT_EQ(1, m2);
    }
}

bool is_primitive_root_naive(int m, int g) {
    assert(1 <= g && g < m);
    int x = 1;
    for (int i = 1; i <= m - 2; i++) {
        x = (int)((long long)(x)*g % m);
        // x == n^i
        if (x == 1) return false;
    }
    x = (int)((long long)(x)*g % m);
    assert(x == 1);
    return true;
}

TEST(UtilsMathTest, IsPrimitiveRootTest) {
    for (int m = 2; m <= 500; m++) {
        if (!atcoder::internal::is_prime_constexpr(m)) continue;
        for (int g = 1; g < m; g++) {
            ASSERT_EQ(is_primitive_root_naive(m, g), is_primitive_root(m, g));
        }
    }
}
