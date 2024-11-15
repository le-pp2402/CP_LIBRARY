int sz[N]; int cnt[N];
void pre_dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : g[u]) if (v != p) {
        pre_dfs(v, u); sz[u] += sz[v];
    }
}
void update(int u, int p, int delta) {
    cnt[color[u]] += delta;
    for (auto v : g[u]) if (v != p) update(v, u, delta);
}
void dfs(int u, int p) {
    int bigChild = -1;
    for (auto v : g[u]) if (v != p) if (bigChild == -1 || sz[v] > sz[bigChild]) bigChild = v;
    for (auto v : g[u]) if (v != p && v != bigChild) {
        dfs(v, u); update(v, u, -1);
    }
    if (bigChild != -1) dfs(bigChild, u);
    for (auto v : g[u]) if (v != p && v != bigChild) update(v, u, 1);
    cnt[color[u]]++; // answer query
}
