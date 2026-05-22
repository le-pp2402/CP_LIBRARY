struct seg {
  int l, r;
  int bestId;
};

// a < b <= c < d
// w(a, c) + w(b, d) <= w(a, d) + w(b, c);
int cost(int i, int j) {
  return 0;
};

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  deque<seg> de;
  de.push_back({0, n - 1, 0}); 
  
  vector<int> dp(n);
  dp[0] = a[0];
  
  for (int i = 1; i < n; i++) {
    while (!de.empty() && de.front().r < i) de.pop_front();
    if (!de.empty() && de.front().l < i) de.front().l = i;

    dp[i] = dp[de.front().bestId] + cost(de.front().bestId, i);

    while (!de.empty()) {
      int l = de.back().l;
      int r = de.back().r;
      int bid = de.back().bestId;

      if (dp[bid] + cost(bid, l) >= dp[i] + cost(i, l)) {
        de.pop_back();
      } else {   
        int lo = l, hi = r + 1;

        while (lo + 1 < hi) {
          int mi = (hi + lo) / 2;
          
          if (dp[bid] + cost(bid, mi) <= dp[i] + cost(i, mi)) {
            lo = mi;
          } else {
            hi = mi; 
          }
        }
        
        de.back().r = lo;
        if (hi < n) {
            de.push_back({hi, n - 1, i});
        }
        
        break;
      }
    }
    
    if (de.empty()) {
      if (i + 1 < n) {
          de.push_back({i + 1, n - 1, i});
      }
    }
  }
} 
