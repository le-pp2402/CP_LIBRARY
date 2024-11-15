int n, m; bool joint[maxN]; int timeDfs = 0, bridge = 0;
int low[maxN], num[maxN]; vector <int> g[maxN];
void dfs(int u, int pre) {
    int child = 0;  num[u] = low[u] = ++timeDfs;
    for (int v : g[u]) {
        if (v == pre) continue;
        if (!num[v]) {
dfs(v, u); low[u] = min(low[u], low[v]);
if (low[v] == num[v]) bridge++; child++;
if (u == pre) {
    if (child > 1) joint[u] = true;
} else if (low[v] >= num[u]) joint[u] = true; }
else low[u] = min(low[u], num[v]); } }
