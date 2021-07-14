#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E"

#include <atcoder/all>

using namespace atcoder;
using namespace std;

using ll = long long;
struct S {
    ll sum, len;
};
S op(S a, S b) { return S{a.sum + b.sum, a.len + b.len}; }
S e() { return S{0, 0}; }
S mapping(ll a, S b) { return S{b.sum + b.len * a, b.len}; }
ll composition(ll a, ll b) { return a + b; }
ll id() { return 0; }

int main()
{
    int n; cin >> n;
    vector<vector<int>> G(n);
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        G[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> G[i][j];
        }
    }

    HeavyLightDecomposition hld(G);

    lazy_segtree<S, op, e, ll, mapping, composition, id> segt(vector<S>(n, S{0, 1}));

    int q; cin >> q;
    for (int t = 0; t < q; ++t) {
        int c; cin >> c;
        if (c == 0) {
            int v, w; cin >> v >> w;
            hld.update(0, v, [&](int l, int r) { segt.apply(l, r, w); }, true);
        }
        if (c == 1) {
            int v; cin >> v;
            cout << hld.query(0, v, e(),
                      [&](int l, int r) { return segt.prod(l, r); },
                      [&](S a, S b) { return op(a, b); }, true).sum << endl;
        }
    }

    return 0;
}