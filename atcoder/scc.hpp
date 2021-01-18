#ifndef ATCODER_SCC_HPP
#define ATCODER_SCC_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "atcoder/internal_scc"

namespace atcoder {

struct scc_graph {
  public:
    scc_graph() : internal(0) {}
    explicit scc_graph(int n) : internal(n) {}

    void add_edge(int from, int to) {
        int n = internal.num_vertices();
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        internal.add_edge(from, to);
    }

    std::vector<std::vector<int>> scc() { return internal.scc(); }

  private:
    internal::scc_graph internal;
};

}  // namespace atcoder

#endif  // ATCODER_SCC_HPP
