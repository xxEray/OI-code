#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 * 50 + 5;
const LL MOD = 1e9 + 7;

int n, m, K;

LL fac[N * 2], invfac[N * 2];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL A(LL x, LL y) { return fac[x] * invfac[x - y] % MOD; }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f0[53][N], f[53][N], g[53][N];

LL Cn[N];
void preprocess() {
	Cn[0] = 1;
	for(int i = 1; i <= std::min(n - 1, 200 * 50); i++) Cn[i] = Cn[i - 1] * (n - 1 - i + 1) % MOD * inv(i) % MOD;
}

LL solve() {
	if(K < 0) return qpow(m, n);
	memset(f0, 0, sizeof(f0)), memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
	f0[0][0] = 1;
	for(int j = 0; j < m - 1; j++)
		for(int i = j; i <= j * (K - 1); i++)
			for(int k = 1; k <= K - 1; k++)
				(f0[j + 1][i + k] += f0[j][i] * C(i + k - 1, k - 1)) %= MOD;
	for(int j = 0; j <= m - 1; j++)
		for(int i = 0; i <= j * (K - 1); i++)
			for(int k = 0; k <= j; k++)
				(f[j][i] += f0[k][i] * A(j, k)) %= MOD;
	for(int j = 0; j < m; j++)
		for(int i = 0; i <= j * (K - 1); i++)
			for(int k = 0; k <= K; k++)
				(g[j + 1][i + k] += f[j][i] * C(i + k, k)) %= MOD;
	LL sum1 = 0, sum2 = 0;
	for(int j = 0; j <= m - 1; j++)
		for(int i = 0; i <= j * (K - 1) && n - i - 1 >= 0; i++) {
			LL coe = (j & 1 ? MOD - 1 : 1);
			(sum1 += m * coe % MOD * f[j][i] % MOD * Cn[i] % MOD * qpow(m - j, n - i - 1) % MOD * C(m - 1, j)) %= MOD;
		}
	// printf("sum1 = %lld\n", sum1);
	for(int j = 1; j <= m; j++)
		for(int i = 0; i <= j * (K - 1) + 1 && n - i - 1 >= 0; i++) {
			LL coe = (j & 1 ? MOD - 1 : 1);
			(sum2 += m * coe % MOD * g[j][i] % MOD * Cn[i] % MOD * qpow(m - j, n - i - 1) % MOD * C(m - 1, j - 1)) %= MOD;
		}
	// printf("sum2 = %lld\n", sum2);
	// printf("return %lld\n", (sum1 + sum2) % MOD);
	return (sum1 + sum2) % MOD;
}

int main() {
#ifndef DEBUG
	freopen("pentiment.in", "r", stdin);
	freopen("pentiment.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &K, &m);
	get_factorial(200 * 50 * 2);
	preprocess();
	LL ans = MOD - solve();
	K--;
	(ans += solve()) %= MOD;
	// printf("ans = %lld\n", ans);
	printf("%lld\n", ans * inv(qpow(m, n)) % MOD);
	return 0;
} /*
1000000000 200 50
*/