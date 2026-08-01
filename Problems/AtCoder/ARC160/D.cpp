#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 998244353;

int n, K;
LL m;

LL fac[N * N], invfac[N * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL calc(LL x, int y) { // C(x + y - 1, y - 1)
	y--, x += y;
	// C(x, y)
	if(x < 0 || y < 0 || x < y) return 0;
	LL ret = 1;
	for(LL i = x - y + 1; i <= x; i++) (ret *= i % MOD) %= MOD;
	return ret * invfac[y] % MOD;
}

int main() {
	get_factorial(2000 * 2000);
	scanf("%d%lld%d", &n, &m, &K);
	if(m % K) { puts("0"); return 0; }
	m /= K;
	LL ans = 0;
	for(int i = 0; i <= n - K + 1; i++) {
		(ans += ((i & 1) ? MOD - 1 : 1) * C(n - K + 1, i) % MOD * calc(m - K * i, n + (n - K + 1)) % MOD) %= MOD;
		// printf("ans = %lld\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
}