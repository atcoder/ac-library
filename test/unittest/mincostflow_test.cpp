#include <gtest/gtest.h>

#include <atcoder/mincostflow>
#include <numeric>
#include <tuple>
#include <vector>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(MincostflowTest, Zero) {
    mcf_graph<int, int> g1;
    mcf_graph<int, int> g2(0);
}

template <class edge> void edge_eq(edge expect, edge actual) {
    ASSERT_EQ(expect.from, actual.from);
    ASSERT_EQ(expect.to, actual.to);
    ASSERT_EQ(expect.cap, actual.cap);
    ASSERT_EQ(expect.flow, actual.flow);
    ASSERT_EQ(expect.cost, actual.cost);
}

TEST(MincostflowTest, Simple) {
    mcf_graph<int, int> g(4);
    g.add_edge(0, 1, 1, 1);
    g.add_edge(0, 2, 1, 1);
    g.add_edge(1, 3, 1, 1);
    g.add_edge(2, 3, 1, 1);
    g.add_edge(1, 2, 1, 1);
    auto expect = std::vector<std::pair<int, int>>({{0, 0}, {2, 4}});
    ASSERT_EQ(expect, g.slope(0, 3, 10));
    mcf_graph<int, int>::edge e;

    e = {0, 1, 1, 1, 1};
    edge_eq(e, g.get_edge(0));
    e = {0, 2, 1, 1, 1};
    edge_eq(e, g.get_edge(1));
    e = {1, 3, 1, 1, 1};
    edge_eq(e, g.get_edge(2));
    e = {2, 3, 1, 1, 1};
    edge_eq(e, g.get_edge(3));
    e = {1, 2, 1, 0, 1};
    edge_eq(e, g.get_edge(4));
}

TEST(MincostflowTest, Usage) {
    {
        mcf_graph<int, int> g(2);
        g.add_edge(0, 1, 1, 2);
        ASSERT_EQ(std::make_pair(1, 2), g.flow(0, 1));
    }
    {
        mcf_graph<int, int> g(2);
        g.add_edge(0, 1, 1, 2);
        auto expect = std::vector<std::pair<int, int>>({{0, 0}, {1, 2}});
        ASSERT_EQ(expect, g.slope(0, 1));
    }
}

TEST(MincostflowTest, Assign) {
    mcf_graph<int, int> g;
    g = mcf_graph<int, int>(10);
}

TEST(MincostflowTest, OutOfRange) {
    mcf_graph<int, int> g(10);
    
    EXPECT_DEATH(g.slope(-1, 3), ".*");
    EXPECT_DEATH(g.slope(3, 3), ".*");
}

// https://github.com/atcoder/ac-library/issues/1
TEST(MincostflowTest, SelfLoop) {
    mcf_graph<int, int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 0, 100, 123));

    mcf_graph<int, int>::edge e = {0, 0, 100, 0, 123};
    edge_eq(e, g.get_edge(0));
}

TEST(MincostflowTest, SameCostPaths) {
    mcf_graph<int, int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 1, 1, 1));
    ASSERT_EQ(1, g.add_edge(1, 2, 1, 0));
    ASSERT_EQ(2, g.add_edge(0, 2, 2, 1));
    auto expected = std::vector<std::pair<int, int>>{{0, 0}, {3, 3}};
    ASSERT_EQ(expected, g.slope(0, 2));
}

TEST(MincostflowTest, Invalid) {
    mcf_graph<int, int> g(2);
    // https://github.com/atcoder/ac-library/issues/51
    EXPECT_DEATH(g.add_edge(0, 0, -1, 0), ".*");
    EXPECT_DEATH(g.add_edge(0, 0, 0, -1), ".*");
}
