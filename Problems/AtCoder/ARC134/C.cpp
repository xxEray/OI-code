#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

LL a[N];
LL n, m;

LL inv[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) (ret *= x) %= MOD; if(!(y >>= 1)) return ret; (x *= x) %= MOD; } }
LL C(LL x, LL y) {
	LL ret = 1;
	for(int j = 1; j <= y; j++)
		(ret *= (x - j + 1) * inv[j] % MOD) %= MOD;
	return ret;
}

int main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 2; i <= n; i++) a[1] -= a[i];
	a[1] -= m;
	if(a[1] < 0) { puts("0"); return 0; }
	for(int i = 1; i <= m; i++) inv[i] = qpow(i, MOD - 2);
	LL ans = 1;
	for(int i = 1; i <= n; i++)
		(ans *= C(a[i] + m - 1, m - 1)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}