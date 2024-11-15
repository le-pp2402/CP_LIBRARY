vector<int> g[N]; vector<ii> edge;
void dc_tree(vector<int> &a) {
  int n = a.size(); vector<int> deg(n + 3, 1);
  for (int &i: a) deg[i]++;  int ptr = 1, la = 1;
  while (deg[ptr] != 1) ptr++; la = ptr;
  for (int &i: a) {
    edge.push_back({i, la}); g[i].push_back(la);
    g[la].push_back(i); deg[i]--; deg[la]--;
    if (deg[i] == 1 && i < ptr) { la = i;
    } else { ptr++; while (deg[ptr] != 1) ptr++; la = ptr; } }
  edge.push_back({n + 2, la}); g[la].push_back(n + 2);
  g[n + 2].push_back(la); }
