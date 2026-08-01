#include <cstdio>
#include <filesystem>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

LL qpow(LL a, LL b) {
	LL ret = 1;
	for(; b; b >>= 1) {
		if(b & 1) ret = ret * a % MOD;
		a = a * a % MOD;
	}
	return ret;
}

LL fac[N], invfac[N];

void preprocess(int tot) {
	fac[0] = 1;
	for(int i = 1; i <= tot; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[tot] = qpow(fac[tot], MOD - 2);
	for(int i = tot; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL C(int x, int y) {
	if(x < 0 || y < 0 || x < y) return 0;
	return fac[x] * invfac[x - y] % MOD * invfac[y] % MOD;
}

int n, m, k;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	preprocess(n);
	LL ans = 0;
	for(int i = 0; i <= k; i++)
		ans = (ans + C(n - 1, i) * m % MOD * qpow(m - 1, n - 1 - i) % MOD) % MOD;
	printf("%lld\n", ans);
	return 0;
}