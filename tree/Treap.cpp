mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct node {
  node *l, *r; int key, prior;
  node(int id) {
    l = r = nullptr; key = id; prior = rnd(); } };
struct treap {
  node *root;
  treap() { root = nullptr; }
  void split(node *t, int pos, node *&l, node *&r) {
    if (t == nullptr) { l = r = nullptr; return; }
    if (t->key <= pos) { split(t->r, pos, l, r);
      t->r = l; l = t; } else {
      split(t->l, pos, l, r); t->l = r; r = t; } }
  node* merge(node *l, node *r) {
    if (!l || !r) return l ? l : r;
    if (l->prior < r->prior) { l->r = merge(l->r, r);
    return l; } r->l = merge(l, r->l); return r; }
  node* merge_treap(node *l, node *r) {
    if(!l) return r; if(!r) return l;
    if(l->prior < r->prior) swap(l, r);
    node *L, *R; split(r, l->key, L, R);
    l->r = merge_treap(l->r, R); l->l = merge_treap(L, l->l);
    return l; }
  void insert(int id) {
    node *l, *r; split(root, id, l, r);
    root = merge(merge(l, new node(id)), r); }
  node* erase(int L, int R) {
    node *l, *r, *mid, *mr; split(root, L - 1, l, r);
    split(r, R, mid, mr); root = merge(l, mr); return mid; }
  void combine(node *x) { //combine with another treap
    root = merge_treap(root, x); }
  vector<int> ans;
  void dfs(node* cur) {
    if(!cur) return; ans.push_back(cur -> key);
    dfs(cur -> l); dfs(cur -> r); }
  vector<int> get() { ans.clear(); dfs(root); return ans; } } t[N];
