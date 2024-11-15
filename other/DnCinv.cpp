//(i, x, y)
//(j, u, v)
// i < j
// x <= u
// v <= y
fenwick<int64_t> fw(w + 1);
auto dq = [&](auto &sf, int l, int r) -> void {
  if (l + 1 == r)
    return;
  int mid = (l + r) >> 1;
  sf(sf, l, mid);
  sf(sf, mid, r);
  int i = l, j = mid;
  vector<node> tmp;
  vector<pair<int, int>> his;
  while (i < mid && j < r) {
    if (a[i].x1 <= a[j].x1) {
      fw.modify(a[i].x2, a[i].val);
      his.push_back({a[i].x2, a[i].val});
      tmp.push_back(a[i++]);
    } else {
      ans[a[j].i] += a[j].sign * (fw.get(a[j].x2));
      tmp.push_back(a[j++]);
    }
  }
  while (i < mid)
    tmp.push_back(a[i++]);
  while (j < r) {
    ans[a[j].i] += a[j].sign * fw.get(a[j].x2);
    tmp.push_back(a[j++]);
  }
  for (int k = l; k < r; k++)
    a[k] = tmp[k - l];
  for (auto [u, v] : his)
    fw.modify(u, -v);
  vector<pair<int, int>>().swap(his);
  vector<node>().swap(tmp);
};
