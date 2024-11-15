// divide in to k subarrays , for each calc the square of the sum
// find total min cost
// for (int i = 1; i <= n; i++) a[i] += a[i - 1];
// for (int i = 1; i <= k; i++) {
//   for (int j = 1; j <= n; j++) dp[i][j] = INF; }
// for (int i = 1; i <= n; i++) { dp[1][i] = a[i] * a[i]; }
// for (int i = 2; i <= k; i++) { dnc(i, 1, n, 1, n); } ans = dp[n][k]
const int N = 3001; const int INF = 1e17; int a[N]; int dp[N][N];
i64 cost(int l, int r) { return (a[r] - a[l - 1]) * (a[r] - a[l - 1]); }
void dnc(int id, int l, int r, int u, int v) {
  if (l > r) { return; }
  int m = (l + r) / 2; int opt = u;
  for (int i = u; i <= min(v, m); i++) {
    if (mini(dp[id][m], dp[id - 1][i - 1] + cost(i, m))) { opt = i; } }
  dnc(id, l, m - 1, u, opt); dnc(id, m + 1, r, opt, v); }
