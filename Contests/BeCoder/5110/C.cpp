#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;
const int MAXK = 1000 + 5;
const LL MOD = 998244353;

int n, K;

LL f[N * MAXK][N], g[N * MAXK][N];

LL fac[N * MAXK], invfac[N * MAXK];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return	 x < y || x < 0 || y < 0 ? 0LL : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d%d", &n, &K);
	get_factorial(n * K);
	f[0][0] = 1;
	for(int i = 1; i <= n * K; i++) for(int j = 0; j <= n; j++) {
		(f[i][j] += f[i - 1][j] * inv(n - j)) %= MOD;
		(g[i][j] += g[i - 1][j] * inv(n - j) + f[i - 1][j] * inv(n - j) % MOD * n % MOD * inv(n - j)) %= MOD;
		if(j) {
			LL val = inv(n - j + 1) * C(i - (j - 1) * K - 1, K - 1) % MOD;
			(f[i][j] += f[i - 1][j - 1] * val) %= MOD;
			(g[i][j] += g[i - 1][j - 1] * val + f[i - 1][j - 1] * val % MOD * n % MOD * inv(n - j + 1) % MOD) %= MOD;
		}
	}
	printf("%lld\n", g[n * K][n] * fac[n] % MOD);
	return 0;
} /*
1 404
*/