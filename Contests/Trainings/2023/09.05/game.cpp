#include <bits/stdc++.h>

typedef long long LL;

const int N = 300 + 5;
const LL MOD = 1e9 + 9;
#ifndef DEBUG
const int V = 300;
#else
const int V = 50;
#endif

int n, m;
char sa[N][N];
int a[N], la[N];
int b[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL power10[N];

LL fp[N][N], fs[N][N], g[N][N], h[N][N], tmp[N];

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int sum = 0;
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]), sum += b[i];
	for(int i = 1; i <= n; i++) scanf("%s", sa[i] + 1), la[i] = strlen(sa[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= la[i]; j++) a[i] = (a[i] * 10 + sa[i][j] - '0') % MOD;
	get_factorial(std::max({n, m, sum}));
	power10[0] = 1;
	for(int i = 1; i <= std::max({n, m, sum}); i++) power10[i] = power10[i - 1] * 10 % MOD;
	fp[0][0] = 1;
	for(int i = 0; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < b[j]; k++)
		if(i - k >= 0) (fp[i][j] += fp[i - k][j - 1] * C(i, k)) %= MOD;
	fs[0][m + 1] = 1;
	for(int i = 0; i <= n; i++) for(int j = m; j >= 1; j--) for(int k = 0; k < b[j]; k++)
		if(i - k >= 0) (fs[i][j] += fs[i - k][j + 1] * C(i, k)) %= MOD;
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(fp[i][j]) printf("fp[%d][%d] = %lld\n", i, j, fp[i][j]);
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(fs[i][j]) printf("fs[%d][%d] = %lld\n", i, j, fs[i][j]);
	g[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = V; j >= 0; j--) for(int k = V; k >= 0; k--) g[j][k] = (g[j][k] + (j >= 1 && k >= la[i] ? g[j - 1][k - la[i]] : 0)) % MOD;
		for(int r = 1; r <= i; r++) {
			for(int j = 0; j <= V; j++) for(int k = 0; k <= V; k++) g[j][k] = (g[j][k] - (j >= 1 && k >= la[r] ? g[j - 1][k - la[r]] : 0)) % MOD;
			// printf("i = %d, r = %d:\n", i, r);
			// for(int j = 0; j <= V; j++) for(int k = 0; k <= V; k++) if(g[j][k]) printf("g[%d][%d] = %lld\n", j, k, g[j][k]);
			for(int j = 0; j <= V; j++) tmp[j] = 0;
			for(int j = 0; j <= V; j++) for(int k = 0; k <= V; k++) (tmp[j] += g[j][k] * power10[k]) %= MOD;
			for(int j = 1; j <= V; j++) (tmp[j] += tmp[j - 1]) %= MOD;
			// for(int j = 0; j <= V; j++) if(tmp[j]) printf("tmp[%d] = %lld\n", j, tmp[j]);
			for(int j = 0; j <= i; j++) (h[i][j] += tmp[j - 1] * a[r]) %= MOD;
			for(int j = V; j >= 0; j--) for(int k = V; k >= 0; k--) g[j][k] = (g[j][k] + (j >= 1 && k >= la[r] ? g[j - 1][k - la[r]] : 0)) % MOD;
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= V; j++) if(h[i][j]) printf("h[%d][%d] = %lld\n", i, j, h[i][j]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(i >= b[j]) {
		LL prob = 0;
		for(int k = 0; k <= i - b[j]; k++) (prob += fp[k][j - 1] * fs[i - b[j] - k][j + 1] % MOD) %= MOD;
		// printf("i = %d, b[j] = %d, prob = %lld, h = %lld\n", i, b[j], prob, h[i][b[j]] - h[i - 1][b[j]]);
		(ans += (h[i][b[j]] - h[i - 1][b[j]] + MOD) % MOD * prob % MOD * inv(C(sum, i)) % MOD * invfac[b[j]]) %= MOD;
		// printf("ans = %lld\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
} /*
3 2
2 2
1
23
456
*/