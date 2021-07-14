#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270"

#include <atcoder/all>
#include <map>

using namespace atcoder;
using namespace std;

int op(int a, int b) { return a + b; }
int e() { return 0; }

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> x(N);
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
    }

    vector<vector<int>> G(N);
    for (int i = 0; i < N-1; ++i) {
        int a, b; cin >> a >> b;
        --a, --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // compress
    map<int,int> comp, comp_inv;
    for (auto X : x) comp[X] = -1;
    int comp_size = 0;
    for (auto &p : comp) {
        p.second = comp_size++;
    }
    for (auto p : comp) {
        comp_inv[p.second] = p.first;
    }

    // lca
    auto hld = HeavyLightDecomposition(G);

    // persistent segtree
    PersistentSegmentTree<int, op, e> segt(comp_size);

    map<int, PersistentSegmentTree<int, op, e>::Node*> root;
    vector<int> par(N);

    auto dfs = [&](auto self, int u, int p) -> void {
        par[u] = p;
        root[u] = segt.set(root[p],
                           comp[x[u]], segt.get(root[p], comp[x[u]]) + 1);
        for (int v : G[u]) {
            if (v != p) self(self, v, u);
        }
    };

    root[-1] = segt.build();
    dfs(dfs, 0, -1);

    for (int i = 0; i < Q; ++i)
    {
        int v, w, l; cin >> v >> w >> l; --v, --w;

        // search x s.t. there are more than l numbers less than or equal to x

        int u = hld.lca(v, w);

        auto check = [&](int m) {
            int nv = segt.prod(root[v], 0, m+1),
                    nw = segt.prod(root[w], 0, m+1),
                    nu = segt.prod(root[u], 0, m+1),
                    np = segt.prod(root[par[u]], 0, m+1);

            return nv + nw - nu - np >= l;
        };

        int ng = -1, ok = comp_size - 1;
        while (abs(ok - ng) > 1) {
            int mid = (ng + ok) / 2;
            (check(mid) ? ok : ng) = mid;
        }

        cout << comp_inv[ok] << endl;
    }

    return 0;
}
