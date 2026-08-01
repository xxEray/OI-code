#include <bits/stdc++.h>

typedef long long LL;
const int N = 5000 + 5;
const LL MOD = 998244353;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) {
	if(x < 0 || y < 0 || x < y) return 0;
	else if(x < MOD && y < MOD) return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD;
	else return C(x / MOD, y / MOD) * C(x % MOD, y % MOD) % MOD;
}
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	get_factorial(5000);
	LL n, p, K;
	scanf("%lld%lld%lld", &n, &p, &K);
	for(int i = 0; i <= K; i++) {
		LL ans = 0;
		for(int j = 0; j <= i; j++)
			(ans += ((j & 1) ? MOD - 1 : 1) * C(i, j) % MOD * qpow(p, j * n + (i - j))) %= MOD;
		printf("%lld ", ans * C(n, i) % MOD);
	}
	puts("");
	return 0;
}