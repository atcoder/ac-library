#include <atcoder/all>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    dsu uf(n);
    for (int i = 0; i < q; i++) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);
        if (t == 0) {
            // merge
            uf.merge(u, v);
        } else {
            // find
            if (uf.same(u, v)) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }
}
