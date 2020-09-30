#ifndef AMYLASE_SPANNING_TREE_HPP
#define AMYLASE_SPANNING_TREE_HPP 1

#include <vector>
#include <queue>
#include <atcoder/dsu>

namespace amylase {

    template <class CostType>
    struct spanning_tree {
        struct edge {
            int p, q;
            CostType cost;

            bool operator<(const edge& y) {
                return cost < y.cost;
            }

            bool operator>(const edge& y) {
                return cost > y.cost;
            }
        };

        int v;
        std::vector<edge> g;
        spanning_tree(int _v): v(_v), g(v) {}

        void add_edge(int from, int to, CostType cost) {
            g.push_back((edge){from, to, cost});
        }

        template<class comparator>
        CostType get_cost() {
            std::priority_queue<edge, std::vector<edge>, comparator> q(g.begin(), g.end());

            atcoder::dsu dsu(v);
            CostType tree_cost = 0;
            while (not q.empty()) {
                CostType cost = q.top().cost;
                int x = q.top().p;
                int y = q.top().q;
                q.pop();
                if (dsu.same(x, y)) {
                    continue;
                } else {
                    tree_cost += cost;
                    dsu.merge(x, y);
                }
            }
            return tree_cost;
        }

        CostType get_maximum_cost() {
            return get_cost<std::less<>>();
        }

        CostType get_minimum_cost() {
            return get_cost<std::greater<>>();
        }
    };

}  // namespace amylase

#endif  // AMYLASE_SPANNING_TREE_HPP
