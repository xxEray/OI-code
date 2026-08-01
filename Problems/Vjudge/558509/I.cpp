#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e6 + 5;
const LL MOD = 1e9 + 7;

int n, m;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL power2[2 * N];

int main() {
	get_factorial(5e6);
	power2[0] = 1;
	for(int i = 1; i <= 10000000; i++) power2[i] = power2[i - 1] * 2 % MOD;
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		LL ans = 0;
		for(int i = 0; i <= std::min(n, m); i++) {
			int s = n + m - i - 1;
			(ans += C(n, i) * C(m, i) % MOD * ((i + 2) * power2[s] % MOD + (s ? s * power2[s - 1] % MOD : 0)) % MOD) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}