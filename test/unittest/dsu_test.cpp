#include "atcoder/dsu"

#include <numeric>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(DSUTest, Zero) {
    dsu uf(0);
    ASSERT_EQ(std::vector<std::vector<int>>(), uf.groups());
}

TEST(DSUTest, Empty) {
    dsu uf;
    ASSERT_EQ(std::vector<std::vector<int>>(), uf.groups());
}

TEST(DSUTest, Assign) {
    dsu uf;
    uf = dsu(10);
}

TEST(DSUTest, Simple) {
    dsu uf(2);
    ASSERT_FALSE(uf.same(0, 1));
    int x = uf.merge(0, 1);
    ASSERT_EQ(x, uf.leader(0));
    ASSERT_EQ(x, uf.leader(1));
    ASSERT_TRUE(uf.same(0, 1));
    ASSERT_EQ(2, uf.size(0));
}

TEST(DSUTest, Line) {
    int n = 500000;
    dsu uf(n);
    for (int i = 0; i < n - 1; i++) {
        uf.merge(i, i + 1);
    }
    ASSERT_EQ(n, uf.size(0));
    ASSERT_EQ(1, uf.groups().size());
}

TEST(DSUTest, LineReverse) {
    int n = 500000;
    dsu uf(n);
    for (int i = n - 2; i >= 0; i--) {
        uf.merge(i, i + 1);
    }
    ASSERT_EQ(n, uf.size(0));
    ASSERT_EQ(1, uf.groups().size());
}
