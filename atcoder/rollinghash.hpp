#ifndef ATCODER_ROLLINGHASH_HPP
#define ATCODER_ROLLINGHASH_HPP 1

#include <random>

namespace atcoder {

using namespace std;

struct RollingHash {
    using u64 = uint64_t;

    template<typename S>
    RollingHash(const S &s, u64 base) {
        int n = int(s.size());
        hash.assign(n+1, 0);
        pow.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            hash[i+1] = mul(hash[i], base) + s[i];
            if (hash[i+1] >= MOD) hash[i+1] -= MOD;
            pow[i+1] = mul(pow[i], base);
        }
    }

    u64 get(int l, int r) const {
        u64 ret = hash[r] + MOD - mul(hash[l], pow[r-l]);
        return ret >= MOD ? ret - MOD : ret;
    }

    static u64 gen_base() {
        mt19937 random{random_device{}()};
        uniform_int_distribution<u64> dist(2, MOD-2);
        return dist(random);
    }

private:
    vector<u64> hash, pow;

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
};

}  // namespace atcoder

#endif  // ATCODER_ROLLINGHASH_HPP
