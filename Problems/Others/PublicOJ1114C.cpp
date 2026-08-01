#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 300 + 5;

int n;
LL mod;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL f[N][N], pow2[N];

int main() {
	scanf("%d%lld", &n, &mod);
	get_factorial(n);
	pow2[0] = 1;
	for(int i = 1; i <= n; i++) pow2[i] = pow2[i - 1] * 2 % MOD;
	f[0][0] = 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= i; j++) {
			(f[i + 1][j + 1] += f[i][j] * (i + 1) % MOD) %= MOD;
			for(int k = 0; k <= j; k++) (f[i + 1][j - k] += f[i][j] * C(j, k) % MOD * (pow2[i + 1 - k] - (k == 0) + MOD) % MOD) %= MOD;
		}
	for(int i = 0; i <= n; i++) for(int j = 0; j <= i; j++) if(f[i][j]) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);

	return 0;
}