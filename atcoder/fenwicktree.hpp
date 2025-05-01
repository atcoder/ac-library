#ifndef ATCODER_FENWICKTREE_HPP
#define ATCODER_FENWICKTREE_HPP 1

#include <cassert>
#include <vector>

#include "atcoder/internal_type_traits"

namespace atcoder {

// Reference: https://en.wikipedia.org/wiki/Fenwick_tree
template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}
    explicit fenwick_tree(const T *const a, const int len) : fenwick_tree(len) {
        U p = 0;
        int i, j = -1;
        while (++j < _n)
            data[j] = p += U(a[j]);
        while (--j > 1)
            if ((i = j & (j + 1)) > 0)
                data[j] -= data[i - 1];
    }
    explicit fenwick_tree(const std::vector<T> &v) :
        fenwick_tree(v.data(), int(v.size())) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    std::vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

}  // namespace atcoder

#endif  // ATCODER_FENWICKTREE_HPP
