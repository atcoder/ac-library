#ifndef AMYLASE_REROOTING_HPP
#define AMYLASE_REROOTING_HPP 1

#include <vector>

namespace amylase {

    template <class State, State (*merge)(State, State), State (*init)(), State (*finalize)(State)>
    struct rerooting {
        std::vector<std::vector<int>> tree;
        std::vector<State> upwards;
        std::vector<State> downwards;

        rerooting(int n): tree(n), upwards(n), downwards(n) {}

        void add_edge(int a, int b) {
            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        State upward_dfs(int pos, int parent) {
            State state = init();
            for (int i = 0; i < tree[pos].size(); ++i) {
                const int next = tree[pos][i];
                if (next == parent) {
                    continue;
                }
                state = merge(state, upward_dfs(next, pos));
            }
            return upwards[pos] = finalize(state);
        }

        void downward_dfs(int pos, int parent, State propagate) {
            std::vector<State> accumulates;
            accumulates.push_back(init());
            for (int i = 0; i < tree[pos].size(); ++i) {
                const int next = tree[pos][i];
                const State state = (next == parent) ? propagate : upwards[next];
                accumulates.push_back(merge(accumulates.back(), state));
            }
            downwards[pos] = finalize(accumulates.back());

            State backwards_accumulate = init();
            for (int i = tree[pos].size() - 1; i >= 0; --i) {
                const int next = tree[pos][i];
                if (next == parent) {
                    backwards_accumulate = merge(backwards_accumulate, propagate);
                } else {
                    State next_propagate = finalize(merge(accumulates[i], backwards_accumulate));
                    downward_dfs(next, pos, next_propagate);
                    backwards_accumulate = merge(backwards_accumulate, upwards[next]);
                }
            }
        }

        void calculate() {
            upward_dfs(0, -1);
            downward_dfs(0, -1, init());
        }
    };

}  // namespace amylase

#endif  // AMYLASE_REROOTING_HPP
