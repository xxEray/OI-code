#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const int M = 200 + 5;

int n, m;

struct Barrett {
	LL m_, p_;
	void init() { m_ = ((__int128_t)1 << 64) / p_; }
} mod;
LL operator%(const LL &x, const Barrett &y) { return x - ((__int128_t)x * y.m_ >> 64) * y.p_; }
LL &operator%=(LL &x, const Barrett &y) { return x -= ((__int128_t)x * y.m_ >> 64) * y.p_; }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL fac[M];
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
}

LL stirling[M][M];
void get_stirling() {
	stirling[0][0] = 1;
	for(int i = 1; i <= m; i++) for(int j = 1; j <= i; j++) stirling[i][j] = (j * stirling[i - 1][j] + stirling[i - 1][j - 1]) % mod;
}

LL inv[N];
void get_inv() {
	inv[1] = 1;
	for(int i = 2; i <= n; i++) inv[i] = (mod.p_ - mod.p_ / i) * inv[mod.p_ % i] % mod;
}

LL f[N][M];

void modsub(LL &x) { x >= mod.p_ ? x -= mod.p_ : 0LL; }

int main() {
	scanf("%d%d%lld", &n, &m, &mod.p_);
	mod.init();
	get_factorial(m);
	get_stirling();
	get_inv();
	f[0][0] = 1;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++) {
			LL val = f[i][j] * (n - i) % mod * inv[n - i + j] % mod;
			modsub(f[i + 1][j] += val), modsub(f[i + 1][j + 1] += val);
		}
	for(int i = 1; i <= m; i++) {
		LL ans = 0;
		for(int j = 1; j <= i; j++) (ans += fac[j] * stirling[i][j] % mod * f[n][j]) %= mod;
		printf("%lld\n", ans);
	}
	return 0;
} /*
300000 100 998244353
*/