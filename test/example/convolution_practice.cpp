#include <atcoder/convolution>
#include <atcoder/modint>
#include <cstdio>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<mint> a(n), b(m);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        b[i] = x;
    }

    auto c = convolution(a, b);

    for (int i = 0; i < n + m - 1; i++) {
        printf("%d ", c[i].val());
    }
    printf("\n");

    return 0;
}
