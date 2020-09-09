#include <gtest/gtest.h>

#include <atcoder/twosat>
#include <numeric>

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
