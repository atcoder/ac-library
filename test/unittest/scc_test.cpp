#include "atcoder/scc"
#include "atcoder/modint"
#include <numeric>

#include <gtest/gtest.h>

using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

TEST(SCCTest, Empty) {
    scc_graph graph0;
    ASSERT_EQ(std::vector<std::vector<int>>(), graph0.scc());
    scc_graph graph1(0);
    ASSERT_EQ(std::vector<std::vector<int>>(), graph1.scc());
}

TEST(SCCTest, Assign) {
    scc_graph graph;
    graph = scc_graph(10);
}

TEST(SCCTest, Simple) {
    scc_graph graph(2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    auto scc = graph.scc();
    ASSERT_EQ(1, scc.size());
}

TEST(SCCTest, SelfLoop) {
    scc_graph graph(2);
    graph.add_edge(0, 0);
    graph.add_edge(0, 0);
    graph.add_edge(1, 1);
    auto scc = graph.scc();
    ASSERT_EQ(2, scc.size());
}

TEST(SCCTest, Invalid) {
    scc_graph graph(2);
    EXPECT_DEATH(graph.add_edge(0, 10), ".*");
}
