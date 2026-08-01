#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n, K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL mod(const LL &x) { return x < 0 ? x + MOD : x; }

int main() {
#ifndef DEBUG
	freopen("god.in", "r", stdin);
	freopen("god.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		LL val = mod(qpow(2, i) - 1) * mod(qpow(2, n - i) - 1) % MOD;
		if(val) (ans += qpow((val + 1) % MOD, K)) %= MOD;
		// printf("%d: val1=%lld, ", i, val);
		val = mod(qpow(2, i - 1) - 1) * 2 % MOD * mod(qpow(2, n - i) - 1) % MOD;
		if(val) (ans += MOD - qpow((val + 1) % MOD, K)) %= MOD;
		// printf("val2=%lld\n", val);
	}
	// printf("count = %lld\n", ans);
	printf("%lld\n", ans * inv(qpow(qpow(2, K), n)) % MOD);
	return 0;
}
