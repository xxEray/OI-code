#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const LL MOD = 1e9 + 7;

int n, K, mmx;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0LL : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

LL f[N][N], pref[N][N];

int main() {
	get_factorial(3000);
	scanf("%d%d%d", &n, &K, &mmx);
	K--;
	for(int i = 1; i <= n; i++) {
		if(i <= K + 1) f[i][1] = i;
		for(int j = 1; j <= i; j++) {
			(f[i][j] += pref[i - 1][j - 1] - pref[std::max(i - K - 2, 0)][j - 1] + MOD) %= MOD;
			pref[i][j] = (pref[i - 1][j] + f[i][j]) % MOD;
			// printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
		}
	}
	LL ans = 0;
	for(int m = K + 1; m <= mmx + K + 1; m++)
		for(int i = 0; i < n; i++) {
			int g = gcd(i, n);
			if(m % (n / g)) continue;
			// printf("n = %d, m = %d, K = %d, i = %d, g = %d (h=%lld)\n", n, m, K, i, g, f[g][g - m / (n / g)]);
			(ans += C(g, m / (n / g)) + MOD - f[g][g - m / (n / g)]) %= MOD;
			if(n <= K) (ans += 1) %= MOD;
			// printf("  ans = %lld\n", ans);
		}
	printf("%lld\n", ans * inv(n) % MOD);
	return 0;
} /*
5
7 3 2
6 3 2
5 3 2
4 3 2
19 5 4
*/