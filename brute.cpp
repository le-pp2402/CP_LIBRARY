#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.cpp"
#else
#define debug(...) 42
#endif

using i64 = long long;

void solve() {
    int n;
    cin >> n;

    vector<array<i64, 3>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i][0] >> vec[i][1] >> vec[i][2];  
    }

    sort(vec.begin(), vec.end());  

    vector<i64> f(n);

    for (int i = 0; i < n; ++i) {
        auto [x, a, b] = vec[i];
        f[i] = a + b * x;
        for (int j = 0; j < i; ++j) {
            if (f[i] > f[j] + a + b * (x - vec[j][0])) {
                f[i] = f[j] + a + b * (x - vec[j][0]);
                debug(i, j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << f[i] << "\n";
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    #ifdef LOCAL
    freopen("in", "r", stdin);
    #endif

    int tc = 1;
    // cin >> tc;
    while (tc--) {
        solve();
    }
}
