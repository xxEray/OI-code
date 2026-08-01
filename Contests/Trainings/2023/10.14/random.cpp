#include <bits/stdc++.h>

typedef long long LL;
const LL MOD = 998244353;

int K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

LL solve(LL n, LL p, LL m) {
	// printf("%lld %lld %lld\n", n, p, m);
	if(n) {
		// (m - m/p)^(K-1) * C(e+K-1, e)
		int e = 0;
		for(LL t = n; t % p == 0; t /= p) e++;
		LL ret = qpow((m - m / p + MOD) % MOD, K - 1);
		for(int i = 0; i < e; i++) (ret *= (e + K - 1 - i) * inv(e - i) % MOD) %= MOD;
		return ret;
	} else {
		int em = 0;
		for(LL t = m; t % p == 0; t /= p) em++;
		LL ret = qpow(m % MOD, K);
		LL pe = 1;
		for(int e = 0; e < em; e++, (pe *= p) %= MOD) {
			LL prod = qpow((m - m / p + MOD) % MOD, K - 1) * ((m / pe - m / pe / p + MOD) % MOD) % MOD;
			for(int i = 0; i < e; i++)
				(prod *= (e + K - 1 - i) * inv(e - i) % MOD) %= MOD;
			(ret += MOD - prod) %= MOD;
		}
		return ret;
	}
}

LL n, m;

int main() {
#ifndef DEBUG
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
#endif
	scanf("%d%lld%lld", &K, &n, &m);
	LL ans = 1;
	for(LL i = 2; i * i <= m; i++) if(m % i == 0) {
		LL t = 1;
		while(m % i == 0) m /= i, t *= i;
		(ans *= solve(n % t, i, t)) %= MOD;
	}
	if(m != 1) (ans *= solve(n % m, m, m)) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
187239 0 318077696017
*/