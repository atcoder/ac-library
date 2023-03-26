#include "atcoder/segtree"

#include <string>
#include <vector>

#include <gtest/gtest.h>

using namespace atcoder;

template <class S, S (*op)(S, S), S (*e)()> struct segtree_naive {
    int n;
    std::vector<std::string> d;
    segtree_naive(int _n) : n(_n), d(n, e()) {}

    void set(int p, S x) { d[p] = x; }
    S get(int p) { return d[p]; }
    S prod(int l, int r) {
        S sum = e();
        for (int i = l; i < r; i++) {
            sum = op(sum, d[i]);
        }
        return sum;
    }
    S all_prod() { return prod(0, n); }

    template <bool (*f)(S)> int max_right(int l) {
        S sum = e();
        assert(f(sum));
        for (int i = l; i < n; i++) {
            sum = op(sum, d[i]);
            if (!f(sum)) return i;
        }
        return n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        S sum = e();
        assert(f(sum));
        for (int i = r - 1; i >= 0; i--) {
            sum = op(d[i], sum);
            if (!f(sum)) return i + 1;
        }
        return 0;
    }
};

std::string op(std::string a, std::string b) {
    assert(a == "$" || b == "$" || a <= b);
    if (a == "$") return b;
    if (b == "$") return a;
    return a + b;
}

std::string e() { return "$"; }

using seg = segtree<std::string, op, e>;
using seg_naive = segtree_naive<std::string, op, e>;

TEST(SegtreeTest, Zero) {
    {
        seg s(0);
        ASSERT_EQ("$", s.all_prod());
    }
    {
        seg s;
        ASSERT_EQ("$", s.all_prod());
    }
}

TEST(SegtreeTest, Invalid) {
    EXPECT_THROW(auto s = seg(-1), std::exception);
    seg s(10);

    EXPECT_DEATH(s.get(-1), ".*");
    EXPECT_DEATH(s.get(10), ".*");

    EXPECT_DEATH(s.prod(-1, -1), ".*");
    EXPECT_DEATH(s.prod(3, 2), ".*");
    EXPECT_DEATH(s.prod(0, 11), ".*");
    EXPECT_DEATH(s.prod(-1, 11), ".*");

    EXPECT_DEATH(s.max_right(11, [](std::string) { return true; }), ".*");
    EXPECT_DEATH(s.min_left(-1, [](std::string) { return true; }), ".*");
    EXPECT_DEATH(s.max_right(0, [](std::string) { return false; }), ".*");
}

TEST(SegtreeTest, One) {
    seg s(1);
    ASSERT_EQ("$", s.all_prod());
    ASSERT_EQ("$", s.get(0));
    ASSERT_EQ("$", s.prod(0, 1));
    s.set(0, "dummy");
    ASSERT_EQ("dummy", s.get(0));
    ASSERT_EQ("$", s.prod(0, 0));
    ASSERT_EQ("dummy", s.prod(0, 1));
    ASSERT_EQ("$", s.prod(1, 1));
}

std::string y;
bool leq_y(std::string x) { return x.size() <= y.size(); }

TEST(SegtreeTest, CompareNaive) {
    for (int n = 0; n < 30; n++) {
        seg_naive seg0(n);
        seg seg1(n);
        for (int i = 0; i < n; i++) {
            std::string s = "";
            s += char('a' + i);
            seg0.set(i, s);
            seg1.set(i, s);
        }

        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                ASSERT_EQ(seg0.prod(l, r), seg1.prod(l, r));
            }
        }

        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                y = seg1.prod(l, r);
                ASSERT_EQ(seg0.max_right<leq_y>(l), seg1.max_right<leq_y>(l));
                ASSERT_EQ(seg0.max_right<leq_y>(l),
                          seg1.max_right(l, [&](std::string x) {
                              return x.size() <= y.size();
                          }));
            }
        }

        for (int r = 0; r <= n; r++) {
            for (int l = 0; l <= r; l++) {
                y = seg1.prod(l, r);
                ASSERT_EQ(seg0.min_left<leq_y>(r), seg1.min_left<leq_y>(r));
                ASSERT_EQ(seg0.min_left<leq_y>(r),
                          seg1.min_left(r, [&](std::string x) {
                              return x.size() <= y.size();
                          }));
            }
        }
    }
}

TEST(SegtreeTest, Assign) {
    seg seg0;
    seg0 = seg(10);
}

#if __cplusplus >= 201703L

std::string op_const(const std::string& a, const std::string& b) {
    assert(a == "$" || b == "$" || a <= b);
    if (a == "$") return b;
    if (b == "$") return a;
    return a + b;
}

TEST(SegtreeTest, ConstFunc) {
    segtree<std::string, op_const, e> s1(10);
}

#endif

#if __cplusplus >= 202002L

TEST(SegtreeTest, LambdaFunc) {
    segtree<std::string, [](std::string a, std::string b) {
        return a + b;
    }, []() { return ""; }> s1(10);
}

#endif
