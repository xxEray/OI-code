#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
LL mod;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0LL : fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial() {
	fac[0] = 1;
	for(int i = 1; i <= 1000000; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[1000000] = inv(fac[1000000]);
	for(int i = 1000000; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL sum[N];
LL f(int p, int q) {
	assert(p <= q);
//	printf("p = %d, q = %d\n", p, q);
	int l = std::max(0, (p + n + 1) >> 1), r = std::min(n, (q + n) >> 1);
	if(l > r) return 0;
//	printf("f(%d, %d) = %lld (l=%d, r=%d)\n", p, q, (sum[r] - (l ? sum[l - 1] : 0LL) + mod) % mod, l, r);
	return (sum[r] - (l ? sum[l - 1] : 0LL) + mod) % mod;
}

int main() {
#ifndef DEBUG
	freopen("support.in", "r", stdin);
	freopen("support.out", "w", stdout);
#endif
	scanf("%d%lld", &n, &mod);
	get_factorial();
	for(int i = 0; i <= n; i++) sum[i] = ((i ? sum[i - 1] : 0LL) + C(n, i)) % mod;
	LL ans = 0, last = 0;
	for(int i = 0; i <= n; i++) {
		LL now = 0;
		for(int j = i, k = -i, t = 0; k <= n; k = j + 2, j += 2 * i + 2, t ^= 1) {
			if(t) (now += mod - f(k, j)) %= mod;
			else (now += f(k, j)) %= mod;
		}
		for(int j = -3 * i - 2, k = -i - 2, t = 1; k >= -n; k = j - 2, j -= 2 * i + 2, t ^= 1) {
			if(t) (now += mod - f(j, k)) %= mod;
			else (now += f(j, k)) %= mod;
		}
		(now *= now) %= mod;
//		printf("i = %d, val = %lld\n", i, (now - last + mod) % mod);
		(ans += (now - last + mod) * i % mod) %= mod;
		last = now;
	}
//	printf("ans = %lld\n", ans);
	printf("%lld\n", ans * qpow(inv(4), n) % mod);
	return 0;
}
