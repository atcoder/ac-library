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
