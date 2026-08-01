#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e3 + 5;
const LL MOD = 998244353;

int n;
LL K;
LL a[N], b[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int main() {
	scanf("%d%lld", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		LL prod = b[i];
		for(int j = 1; j <= n; j++) if(j != i) (prod *= (K - a[j] + MOD) % MOD * inv((a[i] - a[j] + MOD) % MOD) % MOD) %= MOD;
		(ans += prod) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}