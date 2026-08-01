#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

LL m;
int n;

LL f[70][2], g[70][2], pow2[70];

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

int main() {
	get_factorial(1e5);
	pow2[0] = 1;
	for(int i = 1; i <= 65; i++) pow2[i] = pow2[i - 1] * 2 % MOD;
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%d", &m, &n);
		if(n == 1) { printf("%lld\n", m % MOD); continue; }
		if(n >= 3) {
			printf("%lld\n", (((m & 1) + m) % MOD) * (((m - (m & 1)) / 2 + 1) % MOD) % MOD * inv2 % MOD);
			continue;
		}
		for(int i = 64; i >= 0; i--) f[i][0] = f[i][1] = g[i][0] = g[i][1] = 0;
		f[64][0] = 1;
		for(int i = 63; i >= 0; i--) {
			int x = (m >> i & 1);
			(f[i][0] += f[i + 1][0]) %= MOD;
			(g[i][0] += g[i + 1][0] + f[i + 1][0] * x * pow2[i]) %= MOD;
			if(x == 0) {
				(f[i][0] += f[i + 1][1]) %= MOD;
				(g[i][0] += g[i + 1][1]) %= MOD;
			}
			if(x == 1) {
				(f[i][1] += f[i + 1][0]) %= MOD;
				(g[i][1] += g[i + 1][0]) %= MOD;
			}
			(f[i][1] += f[i + 1][1]) %= MOD;
			(g[i][1] += g[i + 1][1] + f[i + 1][1] * (x == 0) * pow2[i]) %= MOD;
		}
		// for(int i = 5; i >= 0; i--) printf("%d: f = %lld, %lld, g = %lld, %lld\n", i, f[i][0], f[i][1], g[i][0], g[i][1]);
		printf("%lld\n", g[0][0]);
	}
	return 0;
} /*
1
5 2
*/