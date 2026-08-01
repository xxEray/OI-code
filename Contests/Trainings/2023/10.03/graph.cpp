#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N];

LL fac[2 * N], invfac[2 * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL match[2 * N], f[N][N], g[N][2 * N], h[2 * N];
LL powerinv2[N], power2[N];
int pre[3][N];

int main() {
// #ifndef DEBUG
// 	freopen("graph.in", "r", stdin);
// 	freopen("graph.out", "w", stdout);
// #endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 2; i <= n; i++) a[i]--;
	for(int i = 1; i <= n; i++) pre[1][i] = pre[1][i - 1] + (a[i] == 1), pre[2][i] = pre[2][i - 1] + (a[i] == 2);
	get_factorial(2 * n + 1);
	powerinv2[0] = 1, power2[0] = 1;
	for(int i = 1; i <= n; i++) powerinv2[i] = powerinv2[i - 1] * inv(2) % MOD, power2[i] = power2[i - 1] * 2 % MOD;
	match[0] = 1;
	for(int i = 2; i <= 2 * n + 2; i += 2) match[i] = match[i - 2] * (i - 1) % MOD;
	for(int x = 0; x <= 2 * n + 1; x++)
		for(int i = 0; i <= x / 2; i++)
			(h[x] += (((x - i) & 1) ? MOD - 1 : 1) * C(x, 2 * i) % MOD * match[2 * i] % MOD * power2[i]) %= MOD;
	// for(int i = 0; i <= 2 * n + 1; i++) printf("h[%d] = %lld\n", i, h[i]);
	f[1][a[1]] = 1;
	for(int i = 1; i <= n; i++) {
		for(int p = 0; p <= 2 * i + 1; p++) if(g[i][p])
			for(int k = (p & 1); k <= std::min(p, n - i); k++)
				(f[i][k] += g[i][p] * C(p, k) % MOD * match[p - k] % MOD * fac[k]) %= MOD;
		for(int j = 1; j <= n - i; j++) if(f[i][j]) {
			int c1 = pre[1][i + j] - pre[1][i], c2 = pre[2][i + j] - pre[2][i];
			// printf("i = %d, j = %d, c1 = %d, c2 = %d\n", i, j, c1, c2);
			for(int x = 0; x <= c2; x++) {
				int p = c1 + 2 * (c2 - x);
				// printf("    x = %d, p = %d\n", x, p);
				(g[i + j][p] += f[i][j] * powerinv2[c2] % MOD * C(c2, x) % MOD * h[x]) %= MOD;
			}
		}
	}
	// for(int i = 1; i <= n; i++)  {
	// 	for(int j = 0; j <= 2 * n + 1; j++) if(g[i][j]) printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
	// 	for(int j = 0; j <= n - i; j++) if(f[i][j]) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	// }
	printf("%lld\n", f[n][0]);
	return 0;
} /*
3
2 3 3
*/