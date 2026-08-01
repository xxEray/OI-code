#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 998244353;
const int N = 3e6 + 5;

LL n, p;

LL fac[N], invfac[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }

int main() {
#ifndef DEBUG
	freopen("fight.in", "r", stdin);
	freopen("fight.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &p);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % MOD;
	invfac[n] = inv(fac[n]);
	for(int i = n; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	LL ret = 0, last = 0;
	for(int j = n / 2 + 1; j <= n; j++) (last += C(n, j)) %= MOD;
	for(int i = 0; i <= n; i++) {
		// for(int j = (n - i) / 2 + 1; j <= n - i; j++) (tmp += C(n - i, j)) %= MOD;
		if(i) {
			last = (last - C(n - i, (n - i + 1) / 2) + MOD) % MOD * inv(2) % MOD;
			if((n - i) & 1) (last += C(n - i, (n - i) / 2 + 1)) %= MOD;
		}
		// printf("%lld\n", tmp);
		(ret += qpow(p, i) * C(n, i) % MOD * last % MOD * (i + 1) % MOD) %= MOD;
	}
	(ret *= qpow(inv(p + 2), n)) %= MOD;
	printf("%lld\n", ret);
	return 0;
}