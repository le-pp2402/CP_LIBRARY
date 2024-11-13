class wavetree {
  using wt = wavetree;
  private:
    int lo, hi;
    wt *l, *r;
    vector<int> b;
    #define lt (b[l - 1])
    #define rt (b[r])
  public:
    wavetree() {}
    template<class RAIterator>
    wavetree(RAIterator from, RAIterator to, int x, int y) {
      lo = x, hi = y;
      if (lo == hi or from >= to) return;
      int mid = (lo + hi) >> 1;
      auto f = [mid](int x) -> bool {
        return x <= mid;
      };
      b.reserve(to - from + 1);
      b.emplace_back(0);
      for (auto it = from; it != to; ++it) {
        b.emplace_back(b.back() + f(*it));
      }
      auto pivot = stable_partition(from, to, f);
      l = new wavetree(from, pivot, lo, mid);
      r = new wavetree(pivot, to, mid + 1, hi);
    }

    int kth(int l, int r, int k) {
      if (l > r) return 0;
      if (lo == hi) return lo;
      int inLeft = b[r] - b[l - 1];
      if (inLeft >= k) return this -> l -> kth(lt + 1, rt, k);
      return this -> r -> kth(l - lt, r - rt, k - inLeft);
    }

    int LTE(int l, int r, int k) {
      if (l > r || l > k) return 0;
      if (hi <= k) return r - l + 1;
      return this -> l -> LTE(lt + 1, rt, k) + this -> r -> LTE(l - lt, r - rt, k);
    }

    int count(int l, int r, int k) {
      if (l > r || lo > k || hi < k) return 0;
      if (lo == hi) return r - l + 1;
      int mid = (lo + hi) >> 1;
      if (k <= mid) {
        return this -> l -> count(lt + 1, rt, k);
      }
      return this -> r -> count(l - lt, r - rt, k);
    }

};
