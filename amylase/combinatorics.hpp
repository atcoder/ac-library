#ifndef AMYLASE_COMBINATORICS_HPP
#define AMYLASE_COMBINATORICS_HPP 1

#include <vector>

namespace amylase {
    template <class T>
    struct combinatorics {
        std::vector<T> fact_memo;
        combinatorics(): fact_memo(1, 1) {}

        T factorial(long long n) {
            while (fact_memo.size() < n + 1) {
                T next = fact_memo.back() * fact_memo.size();
                fact_memo.emplace_back(next);
            }
            return fact_memo[n];
        }
    };
}  // namespace amylase

#endif  // AMYLASE_COMBINATORICS_HPP
