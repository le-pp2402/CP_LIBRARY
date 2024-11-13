class tarjan {
public:
  vector<int> num, low, del;
  vector<vector<int>> ssc;
  stack<int> stk;
  int timer;
  tarjan(int n) {
    num.assign(n, 0);
    low.assign(n, 0);
    del.assign(n, 0);
    timer = 0;
  }

  void dfs(int u, vector<vector<int>> &g) {
    low[u] = num[u] = ++timer;
    stk.push(u);
    for (int &v : g[u])
      if (!del[v]) {
        if (num[v]) {
          low[u] = min(low[u], num[v]);
        } else {
          dfs(v, g);
          low[u] = min(low[u], low[v]);
        }
      }

    if (low[u] == num[u]) {
      vector<int> elem;
      int v;
      do {
        v = stk.top();
        stk.pop();
        elem.push_back(v);
        del[v] = true;
      } while (u != v);
      ssc.push_back(elem);
    }
  }

  void run(int n, vector<vector<int>> &g) {
    for (int i = 0; i < n; i++)
      if (!del[i])
        dfs(i, g);
  }
};
