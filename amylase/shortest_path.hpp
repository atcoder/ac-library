#ifndef AMYLASE_SHORTEST_PATH_HPP
#define AMYLASE_SHORTEST_PATH_HPP 1

#include <array>
#include <vector>
#include <map>
#include <queue>

namespace amylase {

template <class CostType>
struct shortest_path {
    struct edge { int to; CostType cost; };

    int v;
    std::vector<std::vector<edge> > g;
    shortest_path(int _v): v(_v), g(v) {}

    void add_edge (int from, int to, CostType cost) {
        g[from].push_back((edge){to, cost});
    }
    std::map<int, CostType> get_distances(int init) {
        std::map<int, CostType> min_cost;
        using queue_element = std::pair<CostType, int>;
        std::priority_queue<queue_element, std::vector<queue_element>, std::greater<queue_element>> q;
        min_cost[init] = 0;
        q.emplace(0, init);
        while (not q.empty()) {
            CostType cost = q.top().first;
            int pos = q.top().second;
            q.pop();

            if (cost > min_cost[pos]) {
                continue;
            }

            for (int i = 0; i < g[pos].size(); ++i) {
                int npos = g[pos][i].to;
                CostType ncost = cost + g[pos][i].cost;
                if (min_cost.find(npos) == min_cost.end() || ncost < min_cost[npos]) {
                    min_cost[npos] = ncost;
                    q.emplace(ncost, npos);
                }
            }
        }
        return min_cost;
    }

    CostType get_distance(int s, int t) {
        return get_distances(s)[t];
    }
};

}  // namespace amylase

#endif  // AMYLASE_SHORTEST_PATH_HPP
