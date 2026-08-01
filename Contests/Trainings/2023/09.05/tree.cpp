#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e7 + 5;
const int MOD = 998244353;

int n, Q;
int a[N];

LL fac[N], invfac[N];
LL qpow(LL x, int y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void preprocess() {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[n] = inv(fac[n]);
	for(int i = n; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	preprocess();
	while(Q--) {
		int K, d;
		scanf("%d", &K);
		for(int i = 0; i < K; i++) scanf("%d", &a[i]);
		scanf("%d", &d);
		std::sort(a, a + K);
		a[K] = n;
		LL ans = 0;
		for(int i = 0; i <= K; i++) (ans += C(a[i], d - i) + (i ? MOD - C(a[i - 1], d - i - 1) : 0)) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}