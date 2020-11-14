#include "atcoder/fenwicktree"
#include "atcoder/modint"

#include <numeric>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(FenwickTreeTest, Empty) {
    fenwick_tree<ll> fw_ll;
    ASSERT_EQ(0, fw_ll.sum(0, 0));

    fenwick_tree<modint> fw_modint;
    ASSERT_EQ(0, fw_modint.sum(0, 0).val());
}

TEST(FenwickTreeTest, Assign) {
    fenwick_tree<ll> fw;
    fw = fenwick_tree<ll>(10);
}

TEST(FenwickTreeTest, Zero) {
    fenwick_tree<ll> fw_ll(0);
    ASSERT_EQ(0, fw_ll.sum(0, 0));

    fenwick_tree<modint> fw_modint(0);
    ASSERT_EQ(0, fw_modint.sum(0, 0).val());
}

TEST(FenwickTreeTest, OverFlowULL) {
    fenwick_tree<ull> fw(10);
    for (int i = 0; i < 10; i++) {
        fw.add(i, (1ULL << 63) + i);
    }
    for (int i = 0; i <= 10; i++) {
        for (int j = i; j <= 10; j++) {
            ull sum = 0;
            for (int k = i; k < j; k++) {
                sum += k;
            }
            ASSERT_EQ(((j - i) % 2) ? (1ULL << 63) + sum : sum, fw.sum(i, j));
        }
    }
}

TEST(FenwickTreeTest, NaiveTest) {
    for (int n = 0; n <= 50; n++) {
        fenwick_tree<ll> fw(n);
        for (int i = 0; i < n; i++) {
            fw.add(i, i * i);
        }
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                ll sum = 0;
                for (int i = l; i < r; i++) {
                    sum += i * i;
                }
                ASSERT_EQ(sum, fw.sum(l, r));
            }
        }
    }
}

TEST(FenwickTreeTest, SMintTest) {
    using mint = static_modint<11>;
    for (int n = 0; n <= 50; n++) {
        fenwick_tree<mint> fw(n);
        for (int i = 0; i < n; i++) {
            fw.add(i, i * i);
        }
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                mint sum = 0;
                for (int i = l; i < r; i++) {
                    sum += i * i;
                }
                ASSERT_EQ(sum, fw.sum(l, r));
            }
        }
    }
}

TEST(FenwickTreeTest, MintTest) {
    using mint = modint;
    mint::set_mod(11);
    for (int n = 0; n <= 50; n++) {
        fenwick_tree<mint> fw(n);
        for (int i = 0; i < n; i++) {
            fw.add(i, i * i);
        }
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                mint sum = 0;
                for (int i = l; i < r; i++) {
                    sum += i * i;
                }
                ASSERT_EQ(sum, fw.sum(l, r));
            }
        }
    }
}

TEST(FenwickTreeTest, Invalid) {
    EXPECT_THROW(auto s = fenwick_tree<int>(-1), std::exception);
    fenwick_tree<int> s(10);

    EXPECT_DEATH(s.add(-1, 0), ".*");
    EXPECT_DEATH(s.add(10, 0), ".*");

    EXPECT_DEATH(s.sum(-1, 3), ".*");
    EXPECT_DEATH(s.sum(3, 11), ".*");
    EXPECT_DEATH(s.sum(5, 3), ".*");
}

TEST(FenwickTreeTest, Bound) {
    fenwick_tree<int> fw(10);
    fw.add(3, std::numeric_limits<int>::max());
    fw.add(5, std::numeric_limits<int>::min());
    ASSERT_EQ(-1, fw.sum(0, 10));
    ASSERT_EQ(-1, fw.sum(3, 6));
    ASSERT_EQ(std::numeric_limits<int>::max(), fw.sum(3, 4));
    ASSERT_EQ(std::numeric_limits<int>::min(), fw.sum(4, 10));
}

TEST(FenwickTreeTest, Boundll) {
    fenwick_tree<ll> fw(10);
    fw.add(3, std::numeric_limits<ll>::max());
    fw.add(5, std::numeric_limits<ll>::min());
    ASSERT_EQ(-1, fw.sum(0, 10));
    ASSERT_EQ(-1, fw.sum(3, 6));
    ASSERT_EQ(std::numeric_limits<ll>::max(), fw.sum(3, 4));
    ASSERT_EQ(std::numeric_limits<ll>::min(), fw.sum(4, 10));
}

TEST(FenwickTreeTest, OverFlow) {
    fenwick_tree<int> fw(20);
    std::vector<ll> a(20);
    for (int i = 0; i < 10; i++) {
        int x = std::numeric_limits<int>::max();
        a[i] += x;
        fw.add(i, x);
    }
    for (int i = 10; i < 20; i++) {
        int x = std::numeric_limits<int>::min();
        a[i] += x;
        fw.add(i, x);
    }
    a[5] += 11111;
    fw.add(5, 11111);

    for (int l = 0; l <= 20; l++) {
        for (int r = l; r <= 20; r++) {
            ll sum = 0;
            for (int i = l; i < r; i++) {
                sum += a[i];
            }
            ll dif = sum - fw.sum(l, r);
            ASSERT_EQ(0, dif % (1LL << 32));
        }
    }
}

#ifndef _MSC_VER

TEST(FenwickTreeTest, Int128) {
    fenwick_tree<__int128> fw(20);
    for (int i = 0; i < 20; i++) {
        fw.add(i, i);
    }

    for (int l = 0; l <= 20; l++) {
        for (int r = l; r <= 20; r++) {
            ll sum = 0;
            for (int i = l; i < r; i++) {
                sum += i;
            }
            ASSERT_EQ(sum, fw.sum(l, r));
        }
    }
}

#endif