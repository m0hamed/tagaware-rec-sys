//Language: GNU C++11


#include<bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

const int mod = 1000000007;

struct Mod {
  int num;
  Mod () : num(0) {;}
  Mod (int n) : num((n % mod + mod) % mod) {;}
  operator int() { return num; }
};

Mod operator+(Mod a, Mod b) { return Mod((a.num + b.num) % mod); }
Mod operator-(Mod a, Mod b) { return Mod((mod + a.num - b.num) % mod); }
Mod operator*(Mod a, Mod b) { return Mod(((long long)a.num * b.num) % mod); }
Mod operator+=(Mod &a, Mod b) { return a = a + b; }
Mod operator-=(Mod &a, Mod b) { return a = a - b; }
Mod operator*=(Mod &a, Mod b) { return a = a * b; }
Mod operator^(Mod a, int n) {
  if (n == 0) return Mod(1);
  Mod res = (a * a) ^ (n / 2);
  if (n % 2) res = res * a;
  return res;
}
Mod inv(Mod a) { return a ^ (mod - 2); }
Mod operator/(Mod a, Mod b) { return a * inv(b); }

#define MAX_N 1024000

Mod fact[MAX_N], factinv[MAX_N];
void init() {
  fact[0] = Mod(1); factinv[0] = 1;
  REP(i,MAX_N-1) {
    fact[i+1] = fact[i] * Mod(i+1);
    factinv[i+1] = factinv[i] / Mod(i+1);
  }
}

Mod comb(int a, int b) {
  return fact[a] * factinv[b] * factinv[a-b];
}

const int NMAX = 4008;
Mod dp[NMAX][NMAX];
Mod sum[NMAX];

int main() {
  init();
  REP(n, NMAX) {
    REP(k, NMAX) dp[n][k] = 0;
    sum[n] = 0;
  }

  dp[0][0] = 1;
  for (int n = 1; n < NMAX; ++n) {
    dp[n][1] = dp[n][n] = 1;
  }

  for (int n = 2; n < NMAX; ++n) {
    for (int k = 2; k < n; ++k) {
      dp[n][k] = dp[n - 1][k - 1] + dp[n - 1][k] * (Mod(k));
    }
  }
  
  for (int n = 1; n < NMAX; ++n) {
    for (int k = 1; k <= n; ++k) {
      sum[n] += dp[n][k];
    }
  }
  sum[0] = 1;

  int n;
  scanf("%d", &n);
  Mod ans;
  
  for (int k = 1; k <= n; ++k) {
    ans += comb(n, k) * sum[n - k];
  }

  printf("%d\n", ans);
  return 0;
}
