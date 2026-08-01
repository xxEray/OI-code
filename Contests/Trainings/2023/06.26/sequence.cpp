#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 998244353;

int n, m;

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

LL f[2][N];

int main() {
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	get_factorial(n);
	for(int i = 1; i <= m; i++) f[1][i] = C(m, i) * fac[i] % MOD * fac[m - i];
	f[1][m + 1] = fac[m] * m % MOD, f[0][m + 1] = (LL)m * (m - 1) / 2 % MOD * fac[m] % MOD;
	LL sum = 0;
	for(int i = 1; i <= m; i++) (sum += f[1][i]) %= MOD;
	for(int i = m + 2; i <= n; i++) {
		(sum += MOD - f[1][i - m - 1] + f[1][i - 1]) %= MOD;
		f[1][i] = sum;
		f[0][i] = (f[0][i - 1] + m * f[1][i - 1] % MOD + MOD - f[1][i]) % MOD;
	}
	// for(int i = 1; i <= n; i++) printf("f[%d] = %lld, %lld\n", i, f[0][i], f[1][i]);
	printf("%lld\n", (f[0][n] + f[1][n]) % MOD);
	return 0;
} /*
7 4
*/