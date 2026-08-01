#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e7 + 5;

LL n, m, mod_v;

struct Barrett {
	LL m, p;
	void init(LL p_) { p = p_; m = ((__int128_t)1 << 64) / p; }
} mod;
LL operator/(LL x, Barrett y) {
	LL w = (__int128_t)x * y.m >> 64;
	if(x - w * y.p >= y.p) w++;
	// assert(w == x / y.p);
	return w;
}
LL operator%(LL x, Barrett y) {
	LL w = x - ((__int128_t)x * y.m >> 64) * y.p;
	if(w >= y.p) w -= y.p;
	// assert(w == x % y.p);
	return w;
}
LL &operator%=(LL &x, Barrett y) {
	x = x - ((__int128_t)x * y.m >> 64) * y.p;
	if(x >= y.p) x -= y.p;
	return x;
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod_v - 2); }
LL fac[N], invfac[N];
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}
LL C(LL x, LL y) {
	if(x < 0 || y < 0 || x < y) return 0;
	if(x < mod_v) return fac[x] * invfac[y] % mod * invfac[x - y] % mod;
	else return C(x / mod, y / mod) * C(x % mod, y % mod) % mod;
}
LL calc(LL x, LL y) {
	if(y < 0) return 0;
	if(!x) return 1;
	LL ret = 0;
	if(y / mod - (y % mod ? 1 : 0) >= 0) {
		for(int j = 0; j < mod_v; j++) (ret += C(x % mod, j)) %= mod;
		(ret *= calc(x / mod, y / mod - (y % mod ? 1 : 0))) %= mod;
	}
	for(int j = 0; j <= y % mod; j++) (ret += C(x, j + y / mod * mod_v)) %= mod;
	// printf("calc(%lld, %lld) = %lld\n", x, y, ret);
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("dimension.in", "r", stdin);
	freopen("dimension.out", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &mod_v);
	mod.init(mod_v);
	if(n <= m) { printf("%lld\n", (qpow(2, n + 1) - 1 + mod_v) % mod); return 0; }
	get_factorial(mod_v - 1);
	printf("%lld\n", (calc(n + 1, m + 1) - 1 + mod_v) % mod);
	return 0;
} /*
546928569052250649 350344784151740060 19402391

*/