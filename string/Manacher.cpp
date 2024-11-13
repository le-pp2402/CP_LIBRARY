struct manacher {
  string s, t;
  vector<int> dp;

  manacher(string &str) {
    s = str;
    dp.assign(s.size() * 2 + 1, 0);
    work();
  }

  void work() {
    int n = s.size();
    s = " " + s;
    t = ".";
    for (int i = 1; i <= n; i++) {
      t += s[i];
      t += '.';
    }
    string res = "";
    n = t.size();
    t = " " + t;
    int L = 1, R = 0;
    for (int i = 1; i <= n; i++) {
      if (i > R) {
        dp[i] = 0;
      } else {
        dp[i] = min(R - i, dp[L + (R - i)]);
      }
      while (i - dp[i] - 1 >= 1 && i + dp[i] + 1 <= n &&
             t[i - dp[i] - 1] == t[i + dp[i] + 1]) {
        dp[i]++;
      }

      if (i + dp[i] > R) {
        L = i - dp[i];
        R = i + dp[i];
      }
    }
  }
};
