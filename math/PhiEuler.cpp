int phi(int n) {
    int ans = n; for (int i = 2; i * i <= n; i++) { if (n % i == 0) 
    { while (n % i == 0) { n /= i; } ans -= ans / i; } }
    if (n != 1) { ans -= ans / n; } return ans; }
vector<int> phi(n+1);
for(int i = 1; i <= n; i++){ phi[i] += i;
    for(int j = 2*i; j <= n; j += i){ phi[j] -= phi[i]; } }
