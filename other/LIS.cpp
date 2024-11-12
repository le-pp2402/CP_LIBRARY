ll LIS(vector<ll> a) {
  vector<ll> f(n + 2, 1e18);
  f[0] = -1e18;
  for (int i = 0; i < n; i++) {
    int pos = upper_bound(f.begin(), f.end(), a[i]) - f.begin();
    if (pos - 1 >= 0 && f[pos - 1] < a[i] && a[i] < f[pos]) f[pos] = a[i]; 
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    // cout << f[i] << ' ';
    if (f[i] != 1e18) ans++;
  }
  return ans;
}
