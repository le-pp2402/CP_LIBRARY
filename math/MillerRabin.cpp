using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpower(u64 base, u64 e, u64 mod) {}
bool check_composite(u64 n, u64 a, u64 d, int s) {
  u64 x = binpower(a, d, n);
  if (x == 1 || x == n - 1) return false;
  for (int r = 1; r < s; r++) { x = (u128)x * x % n;
    if (x == n - 1) return false; } return true; };
bool MillerRabin(u64 n) {
  if (n < 2) return false; int r = 0; u64 d = n - 1;
  while ((d & 1) == 0) { d >>= 1; r++; }
  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (check_composite(n, a, d, r)) return false; } return true; }
