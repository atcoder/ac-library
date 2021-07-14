#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_B"

#include <atcoder/all>

using namespace atcoder;
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (n > k) {
        cout << 0 << endl;
        return 0;
    }

    using Int = modint1000000007;
    Combination<Int> comb(k);

    cout << (comb.C(k, n) * comb.fact(n)).val() << endl;
}
