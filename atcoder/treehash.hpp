#ifndef ATCODER_TREEHASH_HPP
#define ATCODER_TREEHASH_HPP 1

#include <atcoder/centroid>

namespace atcoder {

using namespace std;

struct TreeHash {
    using u64 = uint64_t;

    TreeHash(const vector<vector<int>>& g_, int seed=0) : g(g_) {
        int n = int(g.size());
        mt19937 random(seed);
        uniform_int_distribution<u64> dist(2, MOD-2);
        for (int i = 0; i < n; ++i) base.emplace_back(dist(random));
    }

    u64 get() {
        vector<u64> hash;
        for (int root : centroid(g)) {
            hash.emplace_back(dfs(root, -1, 0));
        }
        return *min_element(hash.begin(), hash.end());
    }

private:
    vector<u64> base;
    vector<vector<int>> g;
    static const u64 MOD = (1ull << 61) - 1;
    static const u64 MASK31 = (1ull << 31) - 1;

    static u64 mul(u64 a, u64 b) {
        u64 au = a >> 31, ad = a & MASK31;
        u64 bu = b >> 31, bd = b & MASK31;
        u64 mid = ad * bu + au * bd;
        u64 midu = mid >> 31, midd = mid & MASK31;
        u64 t = 2 * (au * bu + midu) + (midd << 31) + ad * bd;
        t = (t >> 61) + (t & MOD);
        return t >= MOD ? t - MOD : t;
    }

    u64 dfs(int u, int p, int d) {
        u64 hash = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            hash = mul(hash, dfs(v, u, d+1));
        }
        hash += base[d];
        return hash >= MOD ? hash - MOD : hash;
    }
};

}  // namespace atcoder

#endif  // ATCODER_TREEHASH_HPP
