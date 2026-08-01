// Don't kill monsters, you dolphin!
// Authored by E-ray from team CDFLS: OPJ BLOCK

#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, K;

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

LL val[N];

int main() {
	scanf("%d%d", &n, &K);
	get_factorial(std::max(n, K) + 1);
	for(int i = 0; i <= n; i++) val[i] = fac[std::min(K, i) + 1] * qpow(i + 1, std::max(K - i, 0)) % MOD;
	// for(int i = 0; i <= n; i++) printf("val[%d] = %lld\n", i, val[i]);
	LL ans = 0;
	for(int i = 0; i <= n; i++) (ans += (val[i] - (i ? val[i - 1] : 0) + MOD) % MOD * fac[n] % MOD * invfac[n - i] % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}