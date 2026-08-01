#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

const int N = 1e5 + 5;

LL n, K;

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

LL ans, count;
void calc(LL a, LL d) {
	if(a <= 0 || d <= 0 || a + d > n) return;
	LL b = (n - a - d) / (K - 1), c = b + 1;
	LL t = (n - a - d) % (K - 1);
	if(!t) t = K - 1;
	if(~b & 1) std::swap(b, c), t = K - 1 - t;
	if(a + t * b + (K - 1 - t) * c + d != n) return;
	// printf("a = %lld, b = %lld, c = %lld, d = %lld, t = %lld\n", a, b, c, d, t);
	LL ret = a * a + d * d + t * ((b * b + 1) / 2) + (K - 1 - t) * (c * c / 2);
	assert((ret - n) % 2 == 0);
	ret = (ret - n) >> 1;
	LL cnt = C(K - 1, t);
	if((t && b == 0) || (K - 1 - t && c == 0)) return;
	if(ret < ans) ans = ret, count = cnt;
	else if(ret == ans) ans = ret, (count += cnt) %= MOD;
}

int main() {
	get_factorial(1e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &n, &K);
		if(K == 1) {
			LL x = n / 2, y = (n + 1) / 2;
			printf("%lld %d\n", x * (x - 1) / 2 + y * (y - 1) / 2, (x == y ? 1 : 2));
			continue;
		}
		ans = LLINF, count = 0;
		double b_ = (double)n / K, a_ = (n - (K - 1) * b_) / 2;
		for(LL a = round(a_) - K - 5; a <= round(a_) + K +  5; a++)
			for(LL d : {a - 1, a, a + 1})
				calc(a, d);
		printf("%lld %lld\n", ans, count);
	}
	return 0;
}