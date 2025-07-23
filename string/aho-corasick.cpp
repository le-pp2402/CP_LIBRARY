constexpr int K = 180;
struct node {
  int next[K], go[K], sf, exit[K], jmp; vector<int> output;
  // int output; 
  node() {
    fill(next, next + K, -1); fill(go, go + K, -1);
    fill(exit, exit + K, -1); sf = -1; jmp = -1;
    // output = 0; }
};
struct AC {
  vector<node> g{node()};
  void add(string &s, int out) {
int id = 0; for (char &c : s) {
  if (g[id].next[(int)c] == -1) {
    g[id].next[(int)c] = g.size();
    g.push_back(node());
  } id = g[id].next[(int)c];
} g[id].output.push_back(out);
  }
  void build() {
    queue<int> qu; qu.push(0);
    while (!qu.empty()) {
      int u = qu.front(); int sl = g[u].sf; qu.pop();
      for (int i = 0; i < K; i++) {
        int nt = g[u].next[i];
        int go_sf = (u ? g[sl].go[i] : 0);
        if (u) { g[u].jmp = (g[sl].output.size() ? sl : g[sl].jmp); }
        if (nt == -1) { g[u].go[i] = go_sf; } else {
          g[u].go[i] = nt; g[nt].sf = go_sf; qu.push(nt); }
      } } } };
