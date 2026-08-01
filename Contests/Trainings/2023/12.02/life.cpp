#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n, m;

LL fac[N], invfac[N], invv[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	invv[1] = 1;
	for(int i = 2; i <= mx; i++) invv[i] = (MOD - MOD / i) * invv[MOD % i] % MOD;
}

int main() {
#ifndef DEBUG
	freopen("life.in", "r", stdin);
	freopen("life.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	get_factorial(m);
	LL prod = 1, ans = 0;
	for(int i = 1; i <= m; i++) {
		if(i > 1) (prod *= (n - (i - 1) + 1) * invv[i - 1] % MOD * ((n - 1) - (i - 1) + 1) % MOD * invv[i - 1] % MOD) %= MOD;
		(ans += prod * invv[i] % MOD * C(m, i) % MOD * fac[i]) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}