#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int a[N];

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

LL f(int n, int t) { return n < t ? 0 : fac[n] * fac[n] % MOD * invfac[n - t] % MOD * invfac[n - t] % MOD * invfac[t] % MOD; }
LL calc(int n, int m, int t) {
	LL ret = 0;
	for(int i = 0; i <= t; i++) (ret += ((i & 1) ? MOD - 1 : 1) * f(m, i) % MOD * f(n - i, t - i)) %= MOD;
	// printf("calc(%d, %d, %d) = %lld\n", n, m, t, ret);
	return ret;
}

int main() {
	get_factorial(2e5);
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if(a[n] == -1) a[n] = n;
		if(a[n] != n) { puts("0"); continue; }
		int lasti = 0, lastv = 0;
		LL ans = 1;
		for(int i = 1; i <= n; i++) if(a[i] != -1) {
			if(a[i] - lastv < 0 || a[i] - lastv > 2 * (i - lasti)) { ans = 0; break; }
			(ans *= calc(i - lastv, lasti - lastv, a[i] - lastv)) %= MOD;
			lasti = i, lastv = a[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}