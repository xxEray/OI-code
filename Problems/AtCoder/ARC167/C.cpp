#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 998244353;

int n, K;
int a[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
LL fact(int x) { return x < 0 ? 0 : fac[x]; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	get_factorial(n);
	LL ans = 0;
	std::sort(a + 1, a + n + 1);
	for(int i = 2; i <= n; i++) (ans += fac[n] * a[i]) %= MOD;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= K; j++)
			(ans += a[i] * ((i - 1) * C(n - i, K - 1) % MOD * fact(n - (K + 1)) % MOD - (i - 1) * C(n - i, 2 * K - j) % MOD * fact(n - 2 * K + i - 2) % MOD + MOD)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}