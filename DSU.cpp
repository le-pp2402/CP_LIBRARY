class DSU {
public:
  vector<int> sz, pa;
  DSU(int n) {
    sz.resize(n);
    pa.resize(n);
    for (int i = 0; i < n; i++) {
      sz[i] = 1;
      pa[i] = i;
    }
  }
  int find(int u) { return (u == pa[u] ? u : pa[u] = find(pa[u])); }
  bool merge(int u, int v) {
    if ((u = find(u)) == (v = find(v)))
      return false;
    if (sz[u] < sz[v])
      swap(u, v);
    pa[v] = u;
    sz[u] += sz[v];
    return true;
  }
};
