#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

LL L;
int n;
LL a[N];

LL powa[N][N], prea[N], sufa[N];

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

LL f[2][N][N];

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	scanf("%lld%d", &L, &n);
	get_factorial(n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	a[n + 1] = L + 1;
	for(int i = 1; i <= n; i++) a[i] = (a[i + 1] - a[i] + MOD) % MOD * inv(L) % MOD;
	for(int i = 1; i <= n; i++) prea[i] = (prea[i - 1] + a[i]) % MOD;
	for(int i = n; i >= 1; i--) sufa[i] = (sufa[i + 1] + a[i]) % MOD;
	for(int i = 1; i <= n; i++) {
		powa[i][0] = 1;
		for(int j = 1; j <= n; j++) powa[i][j] = powa[i][j - 1] * a[i] % MOD;
	}
	f[0][1][1] = 1, f[1][1][0] = a[1];
	for(int i = 1; i < n; i++)
		for(int j = 0; j <= i; j++)
			for(int k = 0; k <= j + 1; k++) {
				if(j + 1 - k == 0) {
					if(j) (f[1][i + 1][0] += f[0][i][j] * powa[i + 1][k] % MOD * C((i - j) + k, k) % MOD) %= MOD;
					(f[1][i + 1][0] += f[1][i][j] * powa[i + 1][k] % MOD * C((i - j - 1) + k, k) % MOD) %= MOD;
				} else {
					if(j) (f[0][i + 1][j + 1 - k] += f[0][i][j] * powa[i + 1][k] % MOD * C((i - j) + k, k) % MOD) %= MOD;
					(f[1][i + 1][j + 1 - k] += f[1][i][j] * powa[i + 1][k] % MOD * C((i - j - 1) + k, k) % MOD) %= MOD;
				}
			}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 0; j <= i; j++)
	// 		printf("f[%d][%d] = %lld,%lld\n", i, j, f[0][i][j], f[1][i][j]);
	LL ans = 0;
	for(int j = 0; j <= n; j++) (ans += f[1][n][j] * (n - j) % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
3 3
1 2 3
*/