#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include <atcoder/all>

using namespace atcoder;
using namespace std;

int main()
{
    int n; cin >> n;
    fps a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
    }
    for (auto x : a.log_inplace()) {
        cout << x.val() << endl;
    }
    return 0;
}