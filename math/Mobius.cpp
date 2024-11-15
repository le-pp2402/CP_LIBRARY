mob[1] = 1
mob[n] = 0 neu ton tai so mu > 1
mob[n] = (-1) ^ r voi r la so uoc nguyen to 

i < j 
count (i, j) gcd(a[i], a[j]) = 1
if (x in a remove else add) 
const int N = 5e5 + 9;
int mob[N];
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}
bool vis[N];
vector<int> d[N];
int mul[N];
void add(int x, int k) {
  for (auto y: d[x]) {
    mul[y] += k;
  }
}
int query(int x) {
  int ans = 0;
  for (auto y: d[x]) { ans += mul[y] * mob[y]; }
  return ans;
}
int a[N];
int32_t main() {
  mobius();
  for (int i = 1; i < N; i++) {
    if (mob[i]) {
      for (int j = i; j < N; j += i) {
        d[j].push_back(i);
      }
    }
  }
  // input
  long long ans = 0;
  while (q--) {
    int i; cin >> i;
    if (vis[i]) {
      ans -= query(a[i]);
      ans += a[i] == 1;
      add(a[i], -1);
    }
    else {
      ans += query(a[i]);
      add(a[i], 1);
    }
    vis[i] ^= 1;
    cout << ans << '\n';
  }
}
