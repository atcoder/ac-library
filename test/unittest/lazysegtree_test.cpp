#include "atcoder/lazysegtree"

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>

using namespace atcoder;
struct starry {
    static int op_ss(int a, int b) { return std::max(a, b); }
    static int op_ts(int a, int b) { return a + b; }
    static int op_tt(int a, int b) { return a + b; }
    static int e_s() { return -1'000'000'000; }
    static int e_t() { return 0; }
};

using starry_seg = lazy_segtree<int,
                                starry::op_ss,
                                starry::e_s,
                                int,
                                starry::op_ts,
                                starry::op_tt,
                                starry::e_t>;

TEST(LazySegtreeTest, Zero) {
    {
        starry_seg s(0);
        ASSERT_EQ(-1'000'000'000, s.all_prod());
    }
    {
        starry_seg s;
        ASSERT_EQ(-1'000'000'000, s.all_prod());
    }
    {
        starry_seg s(10);
        ASSERT_EQ(-1'000'000'000, s.all_prod());
    }
}

TEST(LazySegtreeTest, Assign) {
    starry_seg seg0;
    seg0 = starry_seg(10);
}

TEST(LazySegtreeTest, Invalid) {
    EXPECT_THROW(auto s = starry_seg(-1), std::exception);
    starry_seg s(10);

    EXPECT_DEATH(s.get(-1), ".*");
    EXPECT_DEATH(s.get(10), ".*");

    EXPECT_DEATH(s.prod(-1, -1), ".*");
    EXPECT_DEATH(s.prod(3, 2), ".*");
    EXPECT_DEATH(s.prod(0, 11), ".*");
    EXPECT_DEATH(s.prod(-1, 11), ".*");
}

TEST(LazySegtreeTest, NaiveProd) {
    for (int n = 0; n <= 50; n++) {
        starry_seg seg(n);
        std::vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[i] = (i * i + 100) % 31;
            seg.set(i, p[i]);
        }
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                int e = -1'000'000'000;
                for (int i = l; i < r; i++) {
                    e = std::max(e, p[i]);
                }
                ASSERT_EQ(e, seg.prod(l, r));
            }
        }
    }
}

TEST(LazySegtreeTest, Usage) {
    starry_seg seg(std::vector<int>(10, 0));
    ASSERT_EQ(0, seg.all_prod());
    seg.apply(0, 3, 5);
    ASSERT_EQ(5, seg.all_prod());
    seg.apply(2, -10);
    ASSERT_EQ(-5, seg.prod(2, 3));
    ASSERT_EQ(0, seg.prod(2, 4));
}
