#include "atcoder/internal_math"
#include "atcoder/math"

#include <vector>

std::vector<int> factors(int m) {
    std::vector<int> result;
    for (int i = 2; (long long)(i)*i <= m; i++) {
        if (m % i == 0) {
            result.push_back(i);
            while (m % i == 0) {
                m /= i;
            }
        }
    }
    if (m > 1) result.push_back(m);
    return result;
}

bool is_primitive_root(int m, int g) {
    assert(1 <= g && g < m);
    for (int x : factors(m - 1)) {
        if (atcoder::internal::pow_mod_constexpr(g, (m - 1) / x, m) == 1) return false;
    }
    return true;
}
