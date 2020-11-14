#include "atcoder/internal_math"

#include "../utils/math.hpp"

#include <gtest/gtest.h>
#include <numeric>

using namespace atcoder;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

ll gcd(ll a, ll b) {
    assert(0 <= a && 0 <= b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll pow_mod_naive(ll x, ull n, uint mod) {
    ull y = (x % mod + mod) % mod;
    ull z = 1;
    for (ull i = 0; i < n; i++) {
        z = (z * y) % mod;
    }
    return z % mod;
}

ll floor_sum_naive(ll n, ll m, ll a, ll b) {
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        sum += (a * i + b) / m;
    }
    return sum;
}

bool is_prime_naive(ll n) {
    assert(0 <= n && n <= std::numeric_limits<int>::max());
    if (n == 0 || n == 1) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

TEST(InternalMathTest, Barrett) {
    for (int m = 1; m <= 100; m++) {
        internal::barrett bt(m);
        for (int a = 0; a < m; a++) {
            for (int b = 0; b < m; b++) {
                ASSERT_EQ((a * b) % m, bt.mul(a, b));
            }
        }
    }

    internal::barrett bt(1);
    ASSERT_EQ(0, bt.mul(0, 0));
}

TEST(InternalMathTest, BarrettBorder) {
    const int mod_upper = std::numeric_limits<int>::max();
    for (unsigned int mod = mod_upper; mod >= mod_upper - 20; mod--) {
        internal::barrett bt(mod);
        std::vector<unsigned int> v;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
            v.push_back(mod - i);
            v.push_back(mod / 2 + i);
            v.push_back(mod / 2 - i);
        }
        for (auto a : v) {
            ll a2 = a;
            ASSERT_EQ(((a2 * a2) % mod * a2) % mod, bt.mul(a, bt.mul(a, a)));
            for (auto b : v) {
                ll b2 = b;
                ASSERT_EQ((a2 * b2) % mod, bt.mul(a, b));
            }
        }
    }
}

TEST(InternalMathTest, IsPrime) {
    ASSERT_FALSE(internal::is_prime<121>);
    ASSERT_FALSE(internal::is_prime<11 * 13>);
    ASSERT_TRUE(internal::is_prime<1'000'000'007>);
    ASSERT_FALSE(internal::is_prime<1'000'000'008>);
    ASSERT_TRUE(internal::is_prime<1'000'000'009>);
    for (int i = 0; i <= 10000; i++) {
        ASSERT_EQ(is_prime_naive(i), internal::is_prime_constexpr(i));
    }
    for (int i = 0; i <= 10000; i++) {
        int x = std::numeric_limits<int>::max() - i;
        ASSERT_EQ(is_prime_naive(x), internal::is_prime_constexpr(x));
    }
}

#ifndef _MSC_VER
TEST(InternalMathTest, SafeMod) {
    std::vector<ll> preds;
    for (int i = 0; i <= 100; i++) {
        preds.push_back(i);
        preds.push_back(-i);
        preds.push_back(i);
        preds.push_back(std::numeric_limits<ll>::min() + i);
        preds.push_back(std::numeric_limits<ll>::max() - i);
    }

    for (auto a : preds) {
        for (auto b : preds) {
            if (b <= 0) continue;
            ll ans = (ll)((__int128(a) % b + b) % b);
            ASSERT_EQ(ans, internal::safe_mod(a, b));
        }
    }
}
#endif

TEST(InternalMathTest, InvGcdBound) {
    std::vector<ll> pred;
    for (int i = 0; i <= 10; i++) {
        pred.push_back(i);
        pred.push_back(-i);
        pred.push_back(std::numeric_limits<ll>::min() + i);
        pred.push_back(std::numeric_limits<ll>::max() - i);

        pred.push_back(std::numeric_limits<ll>::min() / 2 + i);
        pred.push_back(std::numeric_limits<ll>::min() / 2 - i);
        pred.push_back(std::numeric_limits<ll>::max() / 2 + i);
        pred.push_back(std::numeric_limits<ll>::max() / 2 - i);

        pred.push_back(std::numeric_limits<ll>::min() / 3 + i);
        pred.push_back(std::numeric_limits<ll>::min() / 3 - i);
        pred.push_back(std::numeric_limits<ll>::max() / 3 + i);
        pred.push_back(std::numeric_limits<ll>::max() / 3 - i);
    }
    pred.push_back(998244353);
    pred.push_back(1'000'000'007);
    pred.push_back(1'000'000'009);
    pred.push_back(-998244353);
    pred.push_back(-1'000'000'007);
    pred.push_back(-1'000'000'009);

    for (auto a : pred) {
        for (auto b : pred) {
            if (b <= 0) continue;
            ll a2 = internal::safe_mod(a, b);
            auto eg = internal::inv_gcd(a, b);
            auto g = gcd(a2, b);
            ASSERT_EQ(g, eg.first);
            ASSERT_LE(0, eg.second);
            ASSERT_LE(eg.second, b / eg.first);
#ifndef _MSC_VER
            ASSERT_EQ(g % b, (unsigned __int128)(eg.second) * a2 % b);
#endif
        }
    }
}

TEST(InternalMathTest, PrimitiveRootTestNaive) {
    for (int m = 2; m <= 10000; m++) {
        if (!internal::is_prime_constexpr(m)) continue;
        int n = internal::primitive_root_constexpr(m);
        ASSERT_LE(1, n);
        ASSERT_LT(n, m);
        int x = 1;
        for (int i = 1; i <= m - 2; i++) {
            x = (int)((long long)(x)*n % m);
            // x == n^i
            ASSERT_NE(1, x);
        }
        x = (int)((long long)(x)*n % m);
        ASSERT_EQ(1, x);
    }
}

TEST(InternalMathTest, PrimitiveRootTemplateTest) {
    ASSERT_TRUE(is_primitive_root(2, (internal::primitive_root<2>)));
    ASSERT_TRUE(is_primitive_root(3, (internal::primitive_root<3>)));
    ASSERT_TRUE(is_primitive_root(5, (internal::primitive_root<5>)));
    ASSERT_TRUE(is_primitive_root(7, (internal::primitive_root<7>)));
    ASSERT_TRUE(is_primitive_root(11, (internal::primitive_root<11>)));
    ASSERT_TRUE(
        is_primitive_root(998244353, (internal::primitive_root<998244353>)));
    ASSERT_TRUE(
        is_primitive_root(1000000007, (internal::primitive_root<1000000007>)));

    ASSERT_TRUE(
        is_primitive_root(469762049, (internal::primitive_root<469762049>)));
    ASSERT_TRUE(
        is_primitive_root(167772161, (internal::primitive_root<167772161>)));
    ASSERT_TRUE(
        is_primitive_root(754974721, (internal::primitive_root<754974721>)));
    ASSERT_TRUE(
        is_primitive_root(324013369, (internal::primitive_root<324013369>)));
    ASSERT_TRUE(
        is_primitive_root(831143041, (internal::primitive_root<831143041>)));
    ASSERT_TRUE(
        is_primitive_root(1685283601, (internal::primitive_root<1685283601>)));
}

TEST(InternalMathTest, PrimitiveRootTest) {
    for (int i = 0; i < 1000; i++) {
        int x = std::numeric_limits<int>::max() - i;
        if (!internal::is_prime_constexpr(x)) continue;
        ASSERT_TRUE(
            is_primitive_root(x, (internal::primitive_root_constexpr(x))));
    }
}
