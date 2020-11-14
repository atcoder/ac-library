#include "atcoder/twosat"

#include <numeric>
#include "../utils/random.hpp"

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(TwosatTest, Empty) {
    two_sat ts0;
    ASSERT_TRUE(ts0.satisfiable());
    ASSERT_EQ(std::vector<bool>({}), ts0.answer());
    two_sat ts1(0);
    ASSERT_TRUE(ts1.satisfiable());
    ASSERT_EQ(std::vector<bool>({}), ts1.answer());
}

TEST(TwosatTest, One) {
    {
        two_sat ts(1);
        ts.add_clause(0, true, 0, true);
        ts.add_clause(0, false, 0, false);
        ASSERT_FALSE(ts.satisfiable());
    }
    {
        two_sat ts(1);
        ts.add_clause(0, true, 0, true);
        ASSERT_TRUE(ts.satisfiable());
        ASSERT_EQ(std::vector<bool>{true}, ts.answer());
    }
    {
        two_sat ts(1);
        ts.add_clause(0, false, 0, false);
        ASSERT_TRUE(ts.satisfiable());
        ASSERT_EQ(std::vector<bool>{false}, ts.answer());
    }
}

TEST(TwosatTest, Assign) {
    two_sat ts;
    ts = two_sat(10);
}

TEST(TwosatTest, StressOK) {
    for (int phase = 0; phase < 10000; phase++) {
        int n = randint(1, 20);
        int m = randint(1, 100);
        std::vector<bool> expect(n);
        for (int i = 0; i < n; i++) {
            expect[i] = randbool();
        }
        two_sat ts(n);
        std::vector<int> xs(m), ys(m), types(m);
        for (int i = 0; i < m; i++) {
            int x = randint(0, n - 1);
            int y = randint(0, n - 1);
            int type = randint(0, 2);
            xs[i] = x;
            ys[i] = y;
            types[i] = type;
            if (type == 0) {
                ts.add_clause(x, expect[x], y, expect[y]);
            } else if (type == 1) {
                ts.add_clause(x, !expect[x], y, expect[y]);
            } else {
                ts.add_clause(x, expect[x], y, !expect[y]);
            }
        }
        ASSERT_TRUE(ts.satisfiable());
        auto actual = ts.answer();
        for (int i = 0; i < m; i++) {
            int x = xs[i], y = ys[i], type = types[i];
            if (type == 0) {
                ASSERT_TRUE(actual[x] == expect[x] || actual[y] == expect[y]);
            } else if (type == 1) {
                ASSERT_TRUE(actual[x] != expect[x] || actual[y] == expect[y]);
            } else {
                ASSERT_TRUE(actual[x] == expect[x] || actual[y] != expect[y]);
            }
        }
    }
}
