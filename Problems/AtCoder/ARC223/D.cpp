#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 998244353;

int n, m, K;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) {
	LL ret = 1;
	for(; y; (x *= x) %= MOD, y >>= 1) if(y & 1) (ret *= x) %= MOD;
	return ret;
}
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_fac(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = qpow(fac[mx], MOD - 2);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL calc(int a, int b) {
	if(a > n || b > m || b > a + K) return 0;
	bool flag = false;
	auto corner = [&](int x, int y) { return C(x + y, x); }; // the number of paths from (0, 0) to (a, b)
	if(b == a + K) flag = true, b--;
	LL res = (corner(b, a) - corner(a + K, b - K) + MOD) % MOD;
	if(flag) b++;
	return res * corner(n - a, m - b) % MOD;
}

int main() {
	get_fac(1e7);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		LL ans = 0;
		for(int i = K; i < n + m; i += 2) {
			int a = (i - K) / 2, b = a + K;
			// printf("(%d, %d) => count=%lld\n", a, b, calc(a, b));
			(ans += b * calc(a, b) % MOD) %= MOD;
		}
		// printf("(%d, %d) => count=%lld\n", n, m, calc(n, m));
		(ans += m * calc(n, m) % MOD) %= MOD;
		printf("%lld\n", ans * qpow(C(n + m, n), MOD - 2) % MOD);
	}
	return 0;
}