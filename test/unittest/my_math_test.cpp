#include <amylase/math>
#include <numeric>

#include <gtest/gtest.h>

using ll = long long;

bool is_prime_naive(ll n) {
    assert(0 <= n && n <= std::numeric_limits<int>::max());
    if (n == 0 || n == 1) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

TEST(MyMathTest, IsPrime) {
    for (long long i = 0; i < 10000; ++i) {
        ASSERT_EQ(is_prime_naive(i), amylase::is_prime(i));
    }
    ASSERT_EQ(is_prime_naive(std::numeric_limits<int>::max()), amylase::is_prime(std::numeric_limits<int>::max()));
}

TEST(MyMathTest, Factor) {
    for (long long i = 1; i < 10000; ++i) {
        const auto fact = amylase::factor(i);
        long long prod = 1;
        for (const auto& p : fact) {
            prod *= p;
            ASSERT_TRUE(amylase::is_prime(p));
        }
        ASSERT_EQ(prod, i);
    }
}
