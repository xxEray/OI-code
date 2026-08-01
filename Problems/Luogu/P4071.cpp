#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

LL fac[N], invfac[N];
LL qpow(LL x, LL y, LL mod = MOD) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod = MOD) { return qpow(x, mod - 2, mod); }
LL C(int x, int y, LL mod = MOD) { return fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx, LL mod = MOD) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx], mod);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL f[N];

int main() {
	get_factorial(1e6);
	f[0] = 1, f[1] = 0;
	for(int i = 2; i <= 1000000; i++) f[i] = ((i - 1) * f[i - 1] % MOD + (i - 1) * f[i - 2] % MOD) % MOD;
	int T; scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%lld\n", C(n, m) * f[n - m] % MOD);
	}
	return 0;
}