#include <cstdio>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

LL qpow(LL x, int y) {
	LL ret = 1;
	for(; y; y >>= 1) {
		if(y & 1) ret = ret * x % MOD;
		x = x * x % MOD;
	}
	return ret;
}

int n;
LL k;

LL f[N];

int main() {
	scanf("%d%lld", &n, &k);
	for(LL i = k; i >= 1; i--) {
		f[i] = qpow(k / i, n);
		for(LL j = i + i; j <= k; j += i) f[i] = (f[i] - f[j] + MOD) % MOD;
	}
	LL ans = 0;
	for(LL i = 1; i <= k; i++) ans = (ans + f[i] * i % MOD) % MOD;
	printf("%lld\n", ans);
	return 0;
}