#include <bits/stdc++.h>

typedef long long LL;

const int N = 10000 + 5;
const int INF = 0x3f3f3f3f;
const LL MOD = 998244353;

int R, B;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
#ifndef DEBUG
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	get_factorial(10000);
	scanf("%d%d", &R, &B);
	LL ans = 0;
	for(int i = 0; i <= R; i++) for(int j = 0; j <= B; j++)
		(ans += C(i + j, i) * C(R + B - i - j, R - i) % MOD * std::min(j ? i / j : INF, B - j ? (R - i) / (B - j) : INF)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}