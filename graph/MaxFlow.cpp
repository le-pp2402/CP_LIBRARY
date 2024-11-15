const int inf = 1E9;
template <class T> struct MaxFlow {
  struct _Edge {
    int to;
    T cap;
    _Edge(int to_, T cap_) : to(to_), cap(cap_) {}
  };
  int n;
  vector<_Edge> e;
  vector<vector<int>> g;
  vector<int> cur, h;
  MaxFlow() {}
  MaxFlow(int n_) { init(n_); }
  void init(int n_) {
    this->n = n_;
    e.clear(); g.assign(n, {});
    cur.resize(n); h.resize(n);
  }
  bool bfs(int s, int t) {
    h.assign(n, -1);
    queue<int> que;
    h[s] = 0;
    que.push(s);
    while (!que.empty()) {
      const int u = que.front(); que.pop();
      for (int i : g[u]) {
        auto [v, c] = e[i];
        if (c > 0 && h[v] == -1) {
          h[v] = h[u] + 1;
          if (v == t) {
            return true;
          }
          que.push(v);
        }
      }
    }
    return false;
  }
  T dfs(int u, int t, T f) {
    if (u == t) {
      return f;
    }
    auto r = f;
    for (int &i = cur[u]; i >= 0; --i) {
      const int j = g[u][i];
      auto [v, c] = e[j];
      if (c > 0 && h[v] == h[u] + 1) {
        auto a = dfs(v, t, min(r, c));
        e[j].cap -= a; e[j ^ 1].cap += a;
        r -= a;
        if (r == 0) {
          return f;
        }
      }
    }
    return f - r;
  }
  void addEdge(int u, int v, T c) {
    g[u].push_back(e.size()); e.emplace_back(v, c);
    g[v].push_back(e.size()); e.emplace_back(u, 0);
  }
  T flow(int s, int t) {
    T ans = 0;
    while (bfs(s, t)) {
      for (int i = 0; i < n; i++) {
        cur[i] = g[i].size() - 1;
      }
      ans += dfs(s, t, numeric_limits<T>::max());
    }
    return ans;
  }
  vector<bool> minCut() {
    vector<bool> c(n);
    for (int i = 0; i < n; i++) {
      c[i] = (h[i] != -1);
    }
    return c;
  }
  struct Edge {
    int from; int to;
    T cap; T flow;
  };
  vector<Edge> edges() {
    vector<Edge> a;
    for (int i = 0; i < e.size(); i += 2) {
      Edge x;
      x.from = e[i + 1].to;
      x.to = e[i].to;
      x.cap = e[i].cap + e[i + 1].cap;
      x.flow = e[i + 1].cap;
      a.push_back(x);
    }
    return a;
  }
  vector<vector<int>> trace(int s_, int t_) {
    vector<int> path;
    for (int i = 0; i < n; i++) {
      cur[i] = g[i].size() - 1;
    }
    vector<vector<int>> paths;
    function<bool(int, int)> find = [&](int u, int t) {
      path.push_back(u);
      if (u == t) {
        return true;
      }
      for (int &i = cur[u]; i >= 0; i--) {
        const int j = g[u][i];
        auto [v, c] = e[j ^ 1]; auto [v1, c1] = e[j];
        if (j % 2)
          continue;
        if (c > 0) {
          find(v1, t);
          i--;
          return true;
        }
      }
      return false;
    };
    while (find(s_, t_)) {
      paths.push_back(path);
      path.clear();
    }
    return paths;
  }
};
