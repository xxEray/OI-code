#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 400 + 5;
const LL MOD = 1e9 + 7;

int n, K;
int a[N], b[N];

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

int X;

LL f[N][N];
void solve() {
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) f[i][j] = 0;
	f[0][0] = 1;
	for(int i = 1, oi = n + 1; i <= n; i++) {
		while(oi > 1 && a[i] + b[oi - 1] <= X) oi--;
		for(int j = 0; j <= n; j++) f[i][j] = ((j ? f[i - 1][j - 1] : 0) * std::max((n - oi + 1) - (j - 1), 0) + f[i - 1][j]) % MOD;
	}
}

LL g[2 * N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	std::sort(a + 1, a + n + 1, [&](int x, int y) { return x > y; });
	std::sort(b + 1, b + n + 1, [&](int x, int y) { return x > y; });
	get_factorial(n);
	LL ans = 0;
	for(X = 1; X <= 800; X++) {
		solve();
		for(int k = 1; k <= K; k++) for(int i = 0; i <= k - 1; i++)
			(g[X] += qpow(MOD - 1, k - 1 - i) * C(n - i, k - 1 - i) % MOD * f[n][n - i] % MOD * fac[i]) %= MOD;
		(g[X] *= inv(fac[n])) %= MOD;
		// if(g[X] - g[X - 1]) printf("X = %d, g = %lld\n", X, (g[X] - g[X - 1] + MOD) % MOD);
		(ans += (g[X] - g[X - 1] + MOD) % MOD * X % MOD) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
10 2
3 1 4 1 5 9 2 6 5 3
2 7 1 8 2 8 1 8 2 8
*/