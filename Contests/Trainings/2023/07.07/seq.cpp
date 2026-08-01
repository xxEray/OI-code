#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 1e9 + 7;

int n, K;
int a[N];

LL fac[N * N * 10], invfac[N * N * 10];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[N * N];

int main() {
#ifndef DEBUG
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
#endif
	get_factorial(25000);
	scanf("%d%d", &n, &K);
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
	for(int i = 1; i <= K; i++) {
		LL prod = 1;
		for(int j = 1; j <= n; j++) (prod *= C(i, a[j])) %= MOD;
		f[i] = prod;
		for(int j = 1; j <= i - 1; j++) (f[i] += MOD - C(sum + i - j, i - j) * f[j] % MOD) %= MOD;
	}
	printf("%lld\n", f[K]);
	return 0;
}
