#include "atcoder/math"

#include <numeric>

#include <gtest/gtest.h>

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
        ll z = a * i + b;
        sum += (z - internal::safe_mod(z, m)) / m;
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

TEST(MathTest, PowMod) {
    auto naive = [&](ll x, ll n, int mod) {
        ll y = internal::safe_mod(x, mod);
        ull z = 1 % mod;
        for (ll i = 0; i < n; i++) {
            z = (z * y) % mod;
        }
        return z;
    };
    for (int a = -100; a <= 100; a++) {
        for (int b = 0; b <= 100; b++) {
            for (int c = 1; c <= 100; c++) {
                ASSERT_EQ(naive(a, b, c), pow_mod(a, b, c));
            }
        }
    }
}

TEST(MathTest, InvBoundHand) {
    const ll minll = std::numeric_limits<ll>::min();
    const ll maxll = std::numeric_limits<ll>::max();
    ASSERT_EQ(inv_mod(-1, maxll), inv_mod(minll, maxll));
    ASSERT_EQ(1, inv_mod(maxll, maxll - 1));
    ASSERT_EQ(maxll - 1, inv_mod(maxll - 1, maxll));
    ASSERT_EQ(2, inv_mod(maxll / 2 + 1, maxll));
}

TEST(MathTest, InvMod) {
    for (int a = -100; a <= 100; a++) {
        for (int b = 1; b <= 1000; b++) {            
            if (gcd(internal::safe_mod(a, b), b) != 1) continue;
            ll c = inv_mod(a, b);
            ASSERT_LE(0, c);
            ASSERT_LT(c, b);
            ASSERT_EQ(1 % b, ((a * c) % b + b) % b);
        }
    }
}

TEST(MathTest, InvModZero) {
    ASSERT_EQ(0, inv_mod(0, 1));
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(0, inv_mod(i, 1));
        ASSERT_EQ(0, inv_mod(-i, 1));
        ASSERT_EQ(0, inv_mod(std::numeric_limits<ll>::min() + i, 1));
        ASSERT_EQ(0, inv_mod(std::numeric_limits<ll>::max() - i, 1));
    }
}

TEST(MathTest, FloorSum) {
    for (int n = 0; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            for (int a = -20; a < 20; a++) {
                for (int b = -20; b < 20; b++) {
                    ASSERT_EQ(floor_sum_naive(n, m, a, b),
                              floor_sum(n, m, a, b));
                }
            }
        }
    }
}

TEST(MathTest, CRTHand) {
    auto res = crt({1, 2, 1}, {2, 3, 2});
    ASSERT_EQ(5, res.first);
    ASSERT_EQ(6, res.second);
}

TEST(MathTest, CRT2) {
    for (int a = 1; a <= 20; a++) {
        for (int b = 1; b <= 20; b++) {
            for (int c = -10; c <= 10; c++) {
                for (int d = -10; d <= 10; d++) {
                    auto res = crt({c, d}, {a, b});
                    if (res.second == 0) {
                        for (int x = 0; x < a * b / gcd(a, b); x++) {
                            ASSERT_TRUE(x % a != c || x % b != d);
                        }
                        continue;
                    }
                    ASSERT_EQ(a * b / gcd(a, b), res.second);
                    ASSERT_EQ(internal::safe_mod(c, a), res.first % a);
                    ASSERT_EQ(internal::safe_mod(d, b), res.first % b);
                }
            }
        }
    }
}

TEST(MathTest, CRT3) {
    for (int a = 1; a <= 5; a++) {
        for (int b = 1; b <= 5; b++) {
            for (int c = 1; c <= 5; c++) {
                for (int d = -5; d <= 5; d++) {
                    for (int e = -5; e <= 5; e++) {
                        for (int f = -5; f <= 5; f++) {
                            auto res = crt({d, e, f}, {a, b, c});
                            ll lcm = a * b / gcd(a, b);
                            lcm = lcm * c / gcd(lcm, c);
                            if (res.second == 0) {
                                for (int x = 0; x < lcm; x++) {
                                    ASSERT_TRUE(x % a != d || x % b != e ||
                                                x % c != f);
                                }
                                continue;
                            }
                            ASSERT_EQ(lcm, res.second);
                            ASSERT_EQ(internal::safe_mod(d, a), res.first % a);
                            ASSERT_EQ(internal::safe_mod(e, b), res.first % b);
                            ASSERT_EQ(internal::safe_mod(f, c), res.first % c);
                        }
                    }
                }
            }
        }
    }
}

TEST(MathTest, CRTOverflow) {
    long long r0 = 0;
    long long r1 = 1'000'000'000'000LL - 2;
    long long m0 = 900577;
    long long m1 = 1'000'000'000'000LL;
    auto res = crt({r0, r1}, {m0, m1});
    ASSERT_EQ(m0 * m1, res.second);
    ASSERT_EQ(r0, res.first % m0);
    ASSERT_EQ(r1, res.first % m1);
}

TEST(MathTest, CRTBound) {
    const ll INF = std::numeric_limits<ll>::max();
    std::vector<ll> pred;
    for (int i = 1; i <= 10; i++) {
        pred.push_back(i);
        pred.push_back(INF - (i - 1));
    }
    pred.push_back(998244353);
    pred.push_back(1'000'000'007);
    pred.push_back(1'000'000'009);

    for (auto ab : std::vector<std::pair<ll, ll>>{{INF, INF},
                                                  {1, INF},
                                                  {INF, 1},
                                                  {7, INF},
                                                  {INF / 337, 337},
                                                  {2, (INF - 1) / 2}}) {
        ll a = ab.first;
        ll b = ab.second;
        for (int ph = 0; ph < 2; ph++) {
            for (ll ans : pred) {
                auto res = crt({ans % a, ans % b}, {a, b});
                ll lcm = a / gcd(a, b) * b;
                ASSERT_EQ(lcm, res.second);
                ASSERT_EQ(ans % lcm, res.first);
            }
            std::swap(a, b);
        }
    }
    std::vector<ll> factor_inf = {49, 73, 127, 337, 92737, 649657};
    do {
        for (ll ans : pred) {
            std::vector<ll> r, m;
            for (ll f : factor_inf) {
                r.push_back(ans % f);
                m.push_back(f);
            }
            auto res = crt(r, m);
            ASSERT_EQ(ans % INF, res.first);
            ASSERT_EQ(INF, res.second);
        }
    } while (next_permutation(factor_inf.begin(), factor_inf.end()));
    std::vector<ll> factor_infn1 = {2, 3, 715827883, 2147483647};
    do {
        for (ll ans : pred) {
            std::vector<ll> r, m;
            for (ll f : factor_infn1) {
                r.push_back(ans % f);
                m.push_back(f);
            }
            auto res = crt(r, m);
            ASSERT_EQ(ans % (INF - 1), res.first);
            ASSERT_EQ(INF - 1, res.second);
        }
    } while (next_permutation(factor_infn1.begin(), factor_infn1.end()));
}

std::vector<int> factors(int m) {
    std::vector<int> result;
    for (int i = 2; (ll)(i)*i <= m; i++) {
        if (m % i == 0) {
            result.push_back(i);
            while (m % i == 0) {
                m /= i;
            }
        }
    }
    if (m > 1) result.push_back(m);
    return result;
}

bool is_primitive_root(int m, int g) {
    assert(1 <= g && g < m);
    auto prs = factors(m - 1);
    for (int x : factors(m - 1)) {
        if (internal::pow_mod_constexpr(g, (m - 1) / x, m) == 1) return false;
    }
    return true;
}

bool is_primitive_root_naive(int m, int g) {
    assert(1 <= g && g < m);
    auto prs = factors(m - 1);
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
