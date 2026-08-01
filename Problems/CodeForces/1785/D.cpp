#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = (1 << 20) + 5;
const LL MOD = 998244353;

int n;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

LL f[21][N];

int main() {
	scanf("%d", &n);
	get_factorial(1 << n);
	f[0][0] = 0;
	for(int i = 1; i <= n; i++) for(int j = 0; j < (1 << n); j++)
	return 0;
}