#ifndef AMYLASE_MATH_HPP
#define AMYLASE_MATH_HPP 1

#include <vector>

namespace amylase {

using li = long long;
li _powmod(const li x, const li n, const li mod) {
    if (n == 0) {
        return 1;
    }
    li sq = _powmod(x, n / 2, mod);
    if (n & 1) {
        return sq * sq % mod * x % mod;
    } else {
        return sq * sq % mod;
    }
}

bool _miller_rabin(const long long x, const std::vector<long long>& witnesses) {
    if (x <= 1) {
        return false;
    }
    if ((x & 1) == 0) {
        return x == 2;
    }
    long long d = x - 1;
    long long s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (const auto& a : witnesses) {
        if (a % x <= 1) {
            continue;
        }
        bool is_composite = true;
        is_composite &= _powmod(a, d, x) != 1;
        long long dd = d;
        for (int i = 0; i < s; ++i) {
            is_composite &= _powmod(a, dd, x) != x - 1;
            dd <<= 1;
        }
        if (is_composite) {
            return false;
        }
    }
    return true;
}

bool is_prime(const long long x) {
    return _miller_rabin(x, {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL});
}

std::vector<long long> factor(long long x) {
    std::vector<long long> factors;
    long long p = 2;
    while (p * p <= x) {
        while (x % p == 0) {
            factors.emplace_back(p);
            x /= p;
        }
        p++;
    }
    if (x > 1) {
        factors.emplace_back(x);
    }
    return factors;
}

}  // namespace amylase

#endif  // AMYLASE_MATH_HPP
