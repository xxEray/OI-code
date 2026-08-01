#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int n, K;
int a[N];

int last[N];

LL f[N];

LL fac[N * 2], invfac[N * 2];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d%d", &n, &K);
	get_factorial(2 * n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0, j = 1; j <= n; j++) {
		while(i < j - 1 && a[j] - a[i + 1] > K) i++;
		last[j] = i;
	}
	// for(int i = 1; i <= n; i++) printf("last[%d] = %d\n", i, last[i]);
	f[0] = 1;
	for(int i = 1; i <= n; i++) {
		(f[i] += f[i - 1] * (n - i) % MOD) %= MOD;
		int x = n - i, y = i - last[i] - 1;
		// (f[i] += f[last[i]] * fac[i - last[i] + 1] % MOD * C((n - i) + (i - last[i] + 1) - 1, (n - i) - 1)) %= MOD;
		(f[i] += f[last[i]] * fac[x + y - 1] % MOD * invfac[x - 1] % MOD) %= MOD;
	}
	// for(int i = 0; i < n; i++) printf("f[%d] = %lld\n", i, f[i]);
	printf("%lld\n", a[n] - a[n - 1] > K ? f[n - 1] : 0);
	return 0;
}