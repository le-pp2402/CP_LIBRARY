struct node {
  int u, rnku, v, rnkv;
  node(int u_, int rnku_, int v_, int rnkv_) {
    this->u = u_; this->rnku = rnku_; this->v = v_; this->rnkv = rnkv_;
  }
};
class DSU {
public:
  int n, comps;
  vector<int> p, rnk;
  vector<node *> checkpoint;
  DSU(int n) {
    this->n = n; this->comps = n;
    p.resize(n + 1); rnk.resize(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i, rnk[i] = 1;
    checkpoint.push_back(new node(-1, -1, -1, -1));
  }
  int find_set(int u) { return (u == p[u] ? u : find_set(p[u])); }
  void newCheckpoint() { checkpoint.push_back(new node(-1, -1, -1, -1)); }
  void rollback() {
    while (!checkpoint.empty() && checkpoint.back()->u != -1) {
      int u = checkpoint.back()->u; int v = checkpoint.back()->v;
      int rnku = checkpoint.back()->rnku; int rnkv = checkpoint.back()->rnkv;
      rnk[u] = rnku; rnk[v] = rnkv;
      p[v] = v;
      rnk[checkpoint.back()->u] = checkpoint.back()->rnku;
      rnk[checkpoint.back()->v] = checkpoint.back()->rnkv;
      p[checkpoint.back()->v] = checkpoint.back()->v;
      this->comps++; checkpoint.pop_back();
    }
    checkpoint.pop_back();
  }
  void union_sets(int u, int v) {
    u = find_set(u); v = find_set(v);
    if (u == v) return;
    if (rnk[u] > rnk[v]) swap(u, v);
    checkpoint.push_back(new node(u, rnk[u], v, rnk[v]));
    p[v] = u;
    if (rnk[u] == rnk[v]) rnk[v]++;
    this->comps -= 1;
  }
};
