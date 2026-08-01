#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 2e6 + 5;
const int MOD = 1e9 + 7;

char s[N];
int n, m;

int fac[N], invfac[N];

int qpow(int x, int y) {
	int ret = 1;
	for(; y; y >>= 1) {
		if(y & 1) ret = (LL)ret * x % MOD;
		x = (LL)x * x % MOD;
	}
	return ret;
}

void preprocess(int tot) {
	fac[0] = 1;
	for(int i = 1; i <= tot; i++) fac[i] = (LL)fac[i - 1] * i % MOD;
	invfac[tot] = qpow(fac[tot], MOD - 2);
	for(int i = tot; i >= 1; i--) invfac[i - 1] = (LL)invfac[i] * i % MOD;
}

LL C(int x, int y) {
	if(x < 0 || y < 0 || x < y) return 0;
	return (LL)fac[x] * invfac[x - y] % MOD * invfac[y] % MOD;
}

int main() {
	scanf("%d%s", &n, s);
	m = strlen(s);
	preprocess(n + m);
	// for(int i = 1; i <= n; i++) printf("%d! mod 10^9+7 = %d\n", i, fac[i]);
	// for(int i = 1; i <= n; i++) printf("1 / %d! mod 10^9+7 = %d\n", i, invfac[i]);
	int ans = 0;
	for(int i = 0; i <= n; i++)
		ans = (ans + (LL)qpow(26, i) * C(n + m - i - 1, m - 1) % MOD * qpow(25, n - i) % MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}