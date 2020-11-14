#include "atcoder/maxflow"
#include "../utils/random.hpp"

#include <numeric>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(MaxflowTest, Zero) {
    mf_graph<int> g1;
    mf_graph<int> g2(0);
}

TEST(MaxflowTest, Assign) {
    mf_graph<int> g;
    g = mf_graph<int>(10);
}

template <class edge> void edge_eq(edge expect, edge actual) {
    ASSERT_EQ(expect.from, actual.from);
    ASSERT_EQ(expect.to, actual.to);
    ASSERT_EQ(expect.cap, actual.cap);
    ASSERT_EQ(expect.flow, actual.flow);
}

TEST(MaxflowTest, Simple) {
    mf_graph<int> g(4);
    ASSERT_EQ(0, g.add_edge(0, 1, 1));
    ASSERT_EQ(1, g.add_edge(0, 2, 1));
    ASSERT_EQ(2, g.add_edge(1, 3, 1));
    ASSERT_EQ(3, g.add_edge(2, 3, 1));
    ASSERT_EQ(4, g.add_edge(1, 2, 1));
    ASSERT_EQ(2, g.flow(0, 3));

    mf_graph<int>::edge e;
    e = {0, 1, 1, 1};
    edge_eq(e, g.get_edge(0));
    e = {0, 2, 1, 1};
    edge_eq(e, g.get_edge(1));
    e = {1, 3, 1, 1};
    edge_eq(e, g.get_edge(2));
    e = {2, 3, 1, 1};
    edge_eq(e, g.get_edge(3));
    e = {1, 2, 1, 0};
    edge_eq(e, g.get_edge(4));

    ASSERT_EQ((std::vector<bool>{true, false, false, false}), g.min_cut(0));
}

TEST(MaxflowTest, NotSimple) {
    mf_graph<int> g(2);
    ASSERT_EQ(0, g.add_edge(0, 1, 1));
    ASSERT_EQ(1, g.add_edge(0, 1, 2));
    ASSERT_EQ(2, g.add_edge(0, 1, 3));
    ASSERT_EQ(3, g.add_edge(0, 1, 4));
    ASSERT_EQ(4, g.add_edge(0, 1, 5));
    ASSERT_EQ(5, g.add_edge(0, 0, 6));
    ASSERT_EQ(6, g.add_edge(1, 1, 7));
    ASSERT_EQ(15, g.flow(0, 1));

    mf_graph<int>::edge e;
    e = {0, 1, 1, 1};
    edge_eq(e, g.get_edge(0));
    e = {0, 1, 2, 2};
    edge_eq(e, g.get_edge(1));
    e = {0, 1, 3, 3};
    edge_eq(e, g.get_edge(2));
    e = {0, 1, 4, 4};
    edge_eq(e, g.get_edge(3));
    e = {0, 1, 5, 5};
    edge_eq(e, g.get_edge(4));

    ASSERT_EQ((std::vector<bool>{true, false}), g.min_cut(0));
}

TEST(MaxflowTest, Cut) {
    mf_graph<int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 1, 2));
    ASSERT_EQ(1, g.add_edge(1, 2, 1));
    ASSERT_EQ(1, g.flow(0, 2));

    mf_graph<int>::edge e;
    e = {0, 1, 2, 1};
    edge_eq(e, g.get_edge(0));
    e = {1, 2, 1, 1};
    edge_eq(e, g.get_edge(1));

    ASSERT_EQ((std::vector<bool>{true, true, false}), g.min_cut(0));
}

TEST(MaxflowTest, Twice) {
    mf_graph<int>::edge e;

    mf_graph<int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 1, 1));
    ASSERT_EQ(1, g.add_edge(0, 2, 1));
    ASSERT_EQ(2, g.add_edge(1, 2, 1));
    
    ASSERT_EQ(2, g.flow(0, 2));

    e = {0, 1, 1, 1};
    edge_eq(e, g.get_edge(0));
    e = {0, 2, 1, 1};
    edge_eq(e, g.get_edge(1));
    e = {1, 2, 1, 1};
    edge_eq(e, g.get_edge(2));

    g.change_edge(0, 100, 10);
    e = {0, 1, 100, 10};
    edge_eq(e, g.get_edge(0));

    ASSERT_EQ(0, g.flow(0, 2));
    ASSERT_EQ(90, g.flow(0, 1));

    e = {0, 1, 100, 100};
    edge_eq(e, g.get_edge(0));
    e = {0, 2, 1, 1};
    edge_eq(e, g.get_edge(1));
    e = {1, 2, 1, 1};
    edge_eq(e, g.get_edge(2));

    ASSERT_EQ(2, g.flow(2, 0));

    e = {0, 1, 100, 99};
    edge_eq(e, g.get_edge(0));
    e = {0, 2, 1, 0};
    edge_eq(e, g.get_edge(1));
    e = {1, 2, 1, 0};
    edge_eq(e, g.get_edge(2));
}

TEST(MaxflowTest, Bound) {
    mf_graph<int>::edge e;

    const int INF = std::numeric_limits<int>::max();
    mf_graph<int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 1, INF));
    ASSERT_EQ(1, g.add_edge(1, 0, INF));
    ASSERT_EQ(2, g.add_edge(0, 2, INF));

    ASSERT_EQ(INF, g.flow(0, 2));

    e = {0, 1, INF, 0};
    edge_eq(e, g.get_edge(0));
    e = {1, 0, INF, 0};
    edge_eq(e, g.get_edge(1));
    e = {0, 2, INF, INF};
    edge_eq(e, g.get_edge(2));
}

TEST(MaxflowTest, BoundUint) {
    mf_graph<unsigned int>::edge e;

    const unsigned int INF = std::numeric_limits<unsigned int>::max();
    mf_graph<unsigned int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 1, INF));
    ASSERT_EQ(1, g.add_edge(1, 0, INF));
    ASSERT_EQ(2, g.add_edge(0, 2, INF));

    ASSERT_EQ(INF, g.flow(0, 2));

    e = {0, 1, INF, 0};
    edge_eq(e, g.get_edge(0));
    e = {1, 0, INF, 0};
    edge_eq(e, g.get_edge(1));
    e = {0, 2, INF, INF};
    edge_eq(e, g.get_edge(2));
}

// https://github.com/atcoder/ac-library/issues/1
TEST(MaxflowTest, SelfLoop) {
    mf_graph<int> g(3);
    ASSERT_EQ(0, g.add_edge(0, 0, 100));

    mf_graph<int>::edge e = {0, 0, 100, 0};
    edge_eq(e, g.get_edge(0));
}

TEST(MaxflowTest, Invalid) {
    mf_graph<int> g(2);
    // https://github.com/atcoder/ac-library/issues/5
    EXPECT_DEATH(g.flow(0, 0), ".*");
    EXPECT_DEATH(g.flow(0, 0, 0), ".*");
}

TEST(MaxflowTest, Stress) {
    for (int phase = 0; phase < 10000; phase++) {
        int n = randint(2, 20);
        int m = randint(1, 100);
        int s, t;
        std::tie(s, t) = randpair(0, n - 1);
        if (randbool()) std::swap(s, t);

        mf_graph<int> g(n);
        for (int i = 0; i < m; i++) {
            int u = randint(0, n - 1);
            int v = randint(0, n - 1);
            int c = randint(0, 10000);
            g.add_edge(u, v, c);
        }
        int flow = g.flow(s, t);
        int dual = 0;
        auto cut = g.min_cut(s);
        std::vector<int> v_flow(n);
        for (auto e: g.edges()) {
            v_flow[e.from] -= e.flow;
            v_flow[e.to] += e.flow;
            if (cut[e.from] && !cut[e.to]) dual += e.cap;
        }
        ASSERT_EQ(flow, dual);
        ASSERT_EQ(-flow, v_flow[s]);
        ASSERT_EQ(flow, v_flow[t]);
        for (int i = 0; i < n; i++) {
            if (i == s || i == t) continue;
            ASSERT_EQ(0, v_flow[i]);
        }
    }
}
