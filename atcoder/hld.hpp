#ifndef ATCODER_HLD_HPP
#define ATCODER_HLD_HPP 1

namespace atcoder {

using namespace std;

// Reference: https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html

struct HeavyLightDecomposition {
    const vector<vector<int>>& G;
    vector<int> par, size, depth, head, vid;
    // par[v]: parent of v
    // size[v]: size of subtree[v]
    // depth[v]: depth of v. depth[root] = 0
    // head[v]: head of row containing v
    // vid[v]: index of v when all the rows are aligned.

    explicit HeavyLightDecomposition(const vector<vector<int>>& g, int root = 0) :
            G(g), par(g.size()), size(g.size()), depth(g.size()),
            head(g.size()), vid(g.size()) {
        dfs(root, -1, 0);
        int k = 0;
        hld(root, root, k);
    }

    int lca(int u, int v) const {
        for (;; v = par[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            if (head[u] == head[v]) {
                if (depth[u] > depth[v]) swap(u, v);
                return u;
            }
        }
    }

    template<typename T, typename Q, typename F>
    T query(int u, int v, const T &id, const Q &q, const F &f, bool edge = false) {
        // Require: f(a, b) == f(b, a)
        T s = id;
        for(;; v = par[head[v]]) {
            if(depth[head[u]] > depth[head[v]]) swap(u, v);
            if(head[u] == head[v]) break;
            s = f(s, q(vid[head[v]], vid[v] + 1));
        }
        return f(s, q(vid[u] + edge, vid[v] + 1));
    }

    template<typename Q>
    void update(int u, int v, const Q &q, bool edge = false) {
        for(;; v = par[head[v]]) {
            if(depth[head[u]] > depth[head[v]]) swap(u, v);
            if(head[u] == head[v]) break;
            q(vid[head[v]], vid[v] + 1);
        }
        q(vid[u] + edge, vid[v] + 1);
    }

private:
    void dfs(int v, int p, int d) {
        par[v] = p; depth[v] = d; size[v] = 1;
        for (int u : G[v]) {
            if (u == p) continue;
            dfs(u, v, d+1);
            size[v] += size[u];
        }
    }

    void hld(int v, int h, int& k) {
        head[v] = h; vid[v] = k++;
        int ma = 0, id = -1;
        for (int u : G[v]) {
            if (u == par[v]) continue;
            if (ma < size[u]) ma = size[u], id = u;
        }
        if (id == -1) return;
        hld(id, h, k);
        for (int u : G[v]) {
            if (u == id or u == par[v]) continue;
            hld(u, u, k);
        }
    }
};

}  // namespace atcoder

#endif  // ATCODER_HLD_HPP
