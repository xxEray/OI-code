#include <bits/stdc++.h>

typedef long long LL;

const int N = 30 + 5;
const LL MOD = 998244353;

LL fac[N * N], invfac[N * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int n, m;

LL f[N][N][N * N];

int main() {
	scanf("%d%d", &n, &m);
	get_factorial(n * n);
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) for(int j = 0; j <= i; j++) for(int k = 0; k <= std::min(i * (i - 1) / 2, m); k++) {
		if(j) for(int t = 0; t <= std::min(j - 1, k); t++) (f[i][j][k] += f[i - 1][j - 1][k - t] * C(j - 1, t) % MOD) %= MOD;
		for(int t = 0; t <= std::min(i - j - 1, k - j); t++) (f[i][j][k] += f[i - 1][j][k - j - t] * C(i - j - 1, t) % MOD) %= MOD;
		// if(f[i][j][k]) printf("f[%d][%d][%d] = %lld\n", i, j, k, f[i][j][k]);
	}
	LL ans = 0;
	for(int j = 0; j <= n; j++) (ans += f[n][j][m]) %= MOD;
	// printf("ans = %lld\n", ans);
	printf("%lld\n", (ans - C(n * (n - 1) / 2, m) + MOD) % MOD);
	return 0;
}