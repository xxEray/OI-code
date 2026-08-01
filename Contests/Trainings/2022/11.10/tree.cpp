#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 180 + 5;
const int M = 50 + 5;
const int MAXK = 18 + 3;
const LL MOD = 998244353;

int n, m, K;

LL f[N][M][M][MAXK], g[M][M][M];

LL fac[M], invfac[M];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void preprocess(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d%d", &m, &n, &K);
	preprocess(50);
	for(int a = 0; a <= 50; a++) for(int b = 0; b <= (a >> 1); b++) for(int c = 0; c <= 50; c++) if(a >= 2 * b && c >= b && c <= a)
		for(int i = 0; i <= b; i++) (g[a][b][c] += qpow(MOD - 1, i) * C(a - 2 * i, c) % MOD * C(b, i) % MOD) %= MOD;
	f[3][1][1][2] = 1;
	for(int d = 0; d <= 18; d++) for(int cnt = 0; cnt <= 180; cnt++) for(int a = 0; a <= 50; a++) for(int b = 0; b <= ((a + 1) >> 1); b++) for(int e = 0; e <= a + 1; e++)
		if(cnt + a + e + 1 <= 180 && a + e <= 50 && e <= 50 && d + 1 <= 18 && a + 1 <= 50)
			(f[cnt + a + e + 1][a + e][e][d + 1] += f[cnt][a][b][d] * g[a + 1][b][e] % MOD) %= MOD;
	LL ans = 0;
	for(int cnt = 0; cnt <= n; cnt++) for(int a = 0; a <= m - 1; a++) for(int b = 0; b <= ((a + 1) >> 1); b++) for(int d = 0; d <= std::min(18, K); d++)
		(ans += f[cnt][a][b][d] * std::min(n - cnt + 1, K - d + 1) % MOD) %= MOD;
	(ans += std::min(n, K)) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
f(cnt, a, b, d) * g(a + 1, b, e) -> f(cnt + a + e + 1, a + e, e, d + 1)
25, 13, 13, 18, e<=13
g(a, b, c) = \sum_{i=0}^b (-1)^i C(a - 2 * i, c)
13, 13, 13, i<=13
*/