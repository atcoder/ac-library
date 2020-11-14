#include "atcoder/convolution"
#include "atcoder/modint"

#include <random>
#include "../utils/random.hpp"

#include <gtest/gtest.h>

using namespace atcoder;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

std::vector<ll> conv_ll_naive(std::vector<ll> a, std::vector<ll> b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<ll> c(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> conv_naive(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<mint> c(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

template <int MOD,
          class T,
          std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> conv_naive(std::vector<T> a, std::vector<T> b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += (T)((ll)a[i] * (ll)b[j] % MOD);
            if (c[i + j] >= MOD) c[i + j] -= MOD;
        }
    }
    return c;
}

TEST(ConvolutionTest, Empty) {
    ASSERT_EQ(std::vector<int>{},
              convolution(std::vector<int>{}, std::vector<int>{}));
    ASSERT_EQ(std::vector<int>{},
              convolution(std::vector<int>{}, std::vector<int>{1, 2}));
    ASSERT_EQ(std::vector<int>{},
              convolution(std::vector<int>{1, 2}, std::vector<int>{}));
    ASSERT_EQ(std::vector<int>{},
              convolution(std::vector<int>{1}, std::vector<int>{}));
    ASSERT_EQ(std::vector<ll>{},
              convolution(std::vector<ll>{}, std::vector<ll>{}));
    ASSERT_EQ(std::vector<ll>{},
              convolution(std::vector<ll>{}, std::vector<ll>{1, 2}));

    ASSERT_EQ(std::vector<modint998244353>{},
              convolution(std::vector<modint998244353>{},
                          std::vector<modint998244353>{}));
    ASSERT_EQ(std::vector<modint998244353>{},
              convolution(std::vector<modint998244353>{},
                          std::vector<modint998244353>{1, 2}));
}

TEST(ConvolutionTest, Mid) {
    std::mt19937 mt;
    int n = 1234, m = 2345;
    std::vector<modint998244353> a(n), b(m);
    
    for (int i = 0; i < n; i++) {
        a[i] = mt();
    }
    for (int i = 0; i < m; i++) {
        b[i] = mt();
    }
    ASSERT_EQ(conv_naive(a, b), convolution(a, b));
}

TEST(ConvolutionTest, SimpleSMod) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;
    using s_mint1 = static_modint<MOD1>;
    using s_mint2 = static_modint<MOD2>;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<s_mint1> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt();
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt();
            }
            ASSERT_EQ(conv_naive(a, b), convolution(a, b));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<s_mint2> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt();
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt();
            }
            ASSERT_EQ(conv_naive(a, b), convolution(a, b));
        }
    }
}

TEST(ConvolutionTest, SimpleInt) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<int> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = int(mt() % MOD1);
            }
            for (int i = 0; i < m; i++) {
                b[i] = int(mt() % MOD1);
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<MOD1>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<int> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = int(mt() % MOD2);
            }
            for (int i = 0; i < m; i++) {
                b[i] = int(mt() % MOD2);
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

TEST(ConvolutionTest, SimpleUint) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<uint> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = uint(mt() % MOD1);
            }
            for (int i = 0; i < m; i++) {
                b[i] = uint(mt() % MOD1);
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<MOD1>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<uint> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = uint(mt() % MOD2);
            }
            for (int i = 0; i < m; i++) {
                b[i] = uint(mt() % MOD2);
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

TEST(ConvolutionTest, SimpleLL) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<ll> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = ll(mt() % MOD1);
            }
            for (int i = 0; i < m; i++) {
                b[i] = ll(mt() % MOD1);
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<998244353>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<ll> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = ll(mt() % MOD2);
            }
            for (int i = 0; i < m; i++) {
                b[i] = ll(mt() % MOD2);
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

TEST(ConvolutionTest, SimpleULL) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<ull> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = ull(mt() % MOD1);
            }
            for (int i = 0; i < m; i++) {
                b[i] = ull(mt() % MOD1);
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<MOD1>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<ull> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = ull(mt() % MOD2);
            }
            for (int i = 0; i < m; i++) {
                b[i] = ull(mt() % MOD2);
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

#ifndef _MSC_VER
TEST(ConvolutionTest, SimpleInt128) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<__int128> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt() % MOD1;
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt() % MOD1;
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<MOD1>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<__int128> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt() % MOD2;
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt() % MOD2;
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

TEST(ConvolutionTest, SimpleUInt128) {
    const int MOD1 = 998244353;
    const int MOD2 = 924844033;

    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<unsigned __int128> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt() % MOD1;
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt() % MOD1;
            }
            ASSERT_EQ(conv_naive<MOD1>(a, b), convolution(a, b));
            ASSERT_EQ(conv_naive<MOD1>(a, b), (convolution<998244353>(a, b)));
        }
    }
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<unsigned __int128> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = mt() % MOD2;
            }
            for (int i = 0; i < m; i++) {
                b[i] = mt() % MOD2;
            }
            ASSERT_EQ(conv_naive<MOD2>(a, b), (convolution<MOD2>(a, b)));
        }
    }
}

#endif

TEST(ConvolutionTest, ConvLL) {
    std::mt19937 mt;
    for (int n = 1; n < 20; n++) {
        for (int m = 1; m < 20; m++) {
            std::vector<ll> a(n), b(m);
            for (int i = 0; i < n; i++) {
                a[i] = ll(mt() % 1'000'000) - 500'000;
            }
            for (int i = 0; i < m; i++) {
                b[i] = ll(mt() % 1'000'000) - 500'000;
            }
            ASSERT_EQ(conv_ll_naive(a, b), convolution_ll(a, b));
        }
    }
}

TEST(ConvolutionTest, ConvLLBound) {
    static constexpr unsigned long long MOD1 = 469762049;  // 2^26
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 754974721;  // 2^24
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    for (int i = -1000; i <= 1000; i++) {
        std::vector<ll> a = {(long long)(0ULL - M1M2 - M1M3 - M2M3 + i)};
        std::vector<ll> b = {1};

        ASSERT_EQ(a, convolution_ll(a, b));
    }
    for (int i = 0; i < 1000; i++) {
        std::vector<ll> a = {std::numeric_limits<ll>::min() + i};
        std::vector<ll> b = {1};

        ASSERT_EQ(a, convolution_ll(a, b));
    }
    for (int i = 0; i < 1000; i++) {
        std::vector<ll> a = {std::numeric_limits<ll>::max() - i};
        std::vector<ll> b = {1};

        ASSERT_EQ(a, convolution_ll(a, b));
    }
}

// https://github.com/atcoder/ac-library/issues/30
TEST(ConvolutionTest, Conv641) {
    // 641 = 128 * 5 + 1
    const int MOD = 641;
    std::vector<ll> a(64), b(65);
    for (int i = 0; i < 64; i++) {
        a[i] = randint(0, MOD - 1);
    }
    for (int i = 0; i < 65; i++) {
        b[i] = randint(0, MOD - 1);
    }

    ASSERT_EQ(conv_naive<MOD>(a, b), convolution<MOD>(a, b));
}

// https://github.com/atcoder/ac-library/issues/30
TEST(ConvolutionTest, Conv18433) {
    // 18433 = 2048 * 9 + 1
    const int MOD = 18433;
    std::vector<ll> a(1024), b(1025);
    for (int i = 0; i < 1024; i++) {
        a[i] = randint(0, MOD - 1);
    }
    for (int i = 0; i < 1025; i++) {
        b[i] = randint(0, MOD - 1);
    }

    ASSERT_EQ(conv_naive<MOD>(a, b), convolution<MOD>(a, b));
}
