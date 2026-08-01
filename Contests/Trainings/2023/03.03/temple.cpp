#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 600 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[2 * N];

int c[2 * N], d[2 * N];
LL f[2 * N][N], g[N];

LL fac[2 * N], invfac[2 * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d", &n);
	get_factorial(2 * n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); a[x] = 1; }
	for(int i = 2 * n; i >= 1; i--) c[i] = c[i + 1] + (a[i] == 0), d[i] = d[i + 1] + (a[i] == 1);
	g[0] = 1;
	for(int i = 1; i <= 2 * n; i++)
		for(int j = 1; j <= i; j++)
			(g[i] += C(i - 1, j - 1) * (j + 1) % MOD * g[j - 1] % MOD * g[i - j] % MOD) %= MOD;
	// for(int i = 1; i <= 2 * n; i++) printf("g[%d] = %lld\n", i, g[i]);
	f[2 * n + 1][0] = 1;
	for(int i = 2 * n; i >= 1; i--)
		for(int j = 0; j <= d[i]; j++)
			if(a[i] == 0) {
				(f[i][j] += f[i + 1][j] * (j - c[i + 1]) % MOD) %= MOD;
			} else {
				(f[i][j] += f[i + 1][j]) %= MOD;
				for(int k = 0; k < j; k++) (f[i][j] += f[i + 1][k] * C(d[i + 1] - k, j - k - 1) % MOD * (j - k + 1) % MOD * g[j - k - 1] % MOD) %= MOD;
			}
	// for(int i = 2 * n; i >= 1; i--) for(int j = 0; j <= n; j++) if(f[i][j]) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	printf("%lld\n", f[1][n] * qpow(inv(2), n) % MOD);
	return 0;
}