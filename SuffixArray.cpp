// @author: Le Phi Phat
// @Test:
// https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
// https://codeforces.com/edu/course/2/lesson/2/4/practice/contest/269119/problem/A
struct SuffixArray {
  vector<int> dp;
  vector<int> id;
  vector<int> lcp;
  int N, K;

  // make sure character '$' less than all possible characters in s
  SuffixArray(string &s) {
    s += "$";
    N = s.size();
    K = __lg(N) + 1;
    dp.assign(N, 0);
    id.assign(N, 0);
    iota(id.begin(), id.end(), 0);
    lcp.assign(N, 0);
    work(s);
  }

  void counting_sort(vector<array<int, 3>> &a) {
    for (auto &j : {1, 0}) {
      vector<int> cnt(N);
      for (auto &x : a) {
        cnt[x[j]]++;
      }
      vector<int> p(N);
      for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] + cnt[i - 1];
      }
      vector<array<int, 3>> na(N);
      for (int i = 0; i < N; i++) {
        na[p[a[i][j]]++] = a[i];
      }
      a.swap(na);
    }
  }

  void work(string &s) {
    sort(id.begin(), id.end(), [&](int i, int j) {
      return pair<char, int>(s[i], i) < pair<char, int>(s[j], j);
    });

    for (int i = 1; i < N; i++) {
      dp[id[i]] = dp[id[i - 1]] + (s[id[i]] != s[id[i - 1]]);
    }

    for (int i = 1; i <= K; ++i) {
      int shift = (1 << (i - 1));
      vector<array<int, 3>> a(N);
      for (int j = 0; j < N; j++) {
        a[j][0] = dp[j];
        a[j][1] = dp[(j + shift) % N];
        a[j][2] = j;
      }

      counting_sort(a);
      for (int j = 0; j < N; j++) {
        id[j] = a[j][2];
      }

      dp[id[0]] = 0;
      for (int j = 1; j < N; j++) {
        if (a[j][0] == a[j - 1][0] && a[j][1] == a[j - 1][1]) {
          dp[id[j]] = dp[id[j - 1]];
        } else {
          dp[id[j]] = dp[id[j - 1]] + 1;
        }
      }
    }

    // build lcp
    int k = 0;
    for (int i = 0; i < N - 1; i++) {
      int pi = dp[i];
      int j = id[pi - 1];
      while (s[i + k] == s[j + k])
        k++;
      lcp[pi] = k;
      k = max(0, k - 1);
    }
  }

  // longest common prefix
  vector<int> getLCP() { return lcp; }
  // return suffix array sorted increase
  vector<int> getId() { return id; }
};