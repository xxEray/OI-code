#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;

int n;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		LL ans = 1;
		for(int i = 1; i <= n; i++) {
			LL p, k;
			scanf("%lld%lld", &p, &k);
			(ans *= k * qpow(p, k - 1) % MOD * (p - 1) % MOD + qpow(p, k)) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}