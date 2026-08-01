#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 4000 + 5;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

int n;
int a[N], b[N];

LL f[M][M];

LL fac[2 * M], invfac[2 * M];
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
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	get_factorial(8000);
	for(int i = 1; i <= n; i++) (f[2000 - a[i]][2000 - b[i]] += 1) %= MOD;
	for(int i = 0; i <= 4000; i++) for(int j = 0; j <= 4000; j++) (f[i][j] += (i ? f[i - 1][j] : 0) + (j ? f[i][j - 1] : 0)) %= MOD;
	LL ans = 0;
	for(int i = 1; i <= n; i++) (ans += f[2000 + a[i]][2000 + b[i]]) %= MOD;
	for(int i = 1; i <= n; i++) (ans += MOD - C(a[i] + a[i] + b[i] + b[i], a[i] + a[i])) %= MOD;
	printf("%lld\n", ans * inv2 % MOD);
	return 0;
}