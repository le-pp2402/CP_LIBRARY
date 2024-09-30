using i64 = long long;

i64 expo(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b = b >> 1;
  }
  return res;
}

i64 mminvprime(i64 a, i64 b) { return expo(a, b - 2, b); }

i64 mod_add(i64 a, i64 b, i64 m) {
  a = a % m;
  b = b % m;
  return (((a + b) % m) + m) % m;
}

i64 mod_mul(i64 a, i64 b, i64 m) {
  a = a % m;
  b = b % m;
  return (((a * b) % m) + m) % m;
}

i64 mod_sub(i64 a, i64 b, i64 m) {
  a = a % m;
  b = b % m;
  return (((a - b) % m) + m) % m;
}

struct Hashing {
  string s;
  int n;
  int primes;
  vector<i64> hMOD = {1000000009, 100000007};
  const i64 B = 31;
  vector<vector<i64>> H, pB, invPB;

  Hashing(string a) {
    primes = hMOD.size();
    H.resize(primes);
    pB.resize(primes);
    invPB.resize(primes);
    s = a;
    n = s.length();
    for (int i = 0; i < primes; i++) {
      pB[i].resize(n + 1);
      invPB[i].resize(n + 1);
      pB[i][0] = 1;
      for (int j = 1; j <= n; j++) {
        pB[i][j] = (B * pB[i][j - 1]) % hMOD[i];
      }
      invPB[i][n] = mminvprime(pB[i][n], hMOD[i]);
      for (int j = n - 1; j >= 0; j--) {
        invPB[i][j] = mod_mul(invPB[i][j + 1], B, hMOD[i]);
      }
    }
    for (int i = 0; i < primes; i++) {
      H[i].resize(n);
      for (int j = 0; j < n; j++) {
        H[i][j] = ((s[j] - 'a' + 1LL) * pB[i][j]) % hMOD[i];
        H[i][j] = (H[i][j] + (j > 0 ? H[i][j - 1] : 0LL)) % hMOD[i];
      }
    }
  }

  vector<i64> get(int l, int r) {
    vector<i64> hash(primes);
    for (int i = 0; i < primes; i++) {
      i64 val1 = H[i][r];
      i64 val2 = l > 0 ? H[i][l - 1] : 0LL;
      hash[i] = mod_mul(mod_sub(val1, val2, hMOD[i]), invPB[i][l], hMOD[i]);
    }
    return hash;
  }
};
