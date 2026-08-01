#include <cstdio>

typedef long long LL;

const int N = 5e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;

LL fac[N], invfac[N];

void preprocess() {
	auto qpow = [=](LL x, int y) -> LL {
		LL prod = 1;
		for(; y; y >>= 1) {
			if(y & 1) prod = (prod * x) % MOD;
			x = (x * x) % MOD;
		}
		return prod;
	};
	fac[0] = 1;
	for(int i = 1; i <= m; i++) fac[i] = (LL)fac[i - 1] * i % MOD;
	invfac[m] = qpow(fac[m], MOD - 2);
	for(int i = m; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

inline LL C(LL a, LL b) {
	if(a < 0 || b < 0 || a < b) return 0;
	else return fac[a] * invfac[b] % MOD * invfac[a - b] % MOD;
}
inline LL A(LL a, LL b) {
	if(a < 0 || b < 0 || a < b) return 0;
	else return fac[a] * invfac[a - b] % MOD;
}
inline LL pow_m1(int y) { return (y & 1) ? MOD - 1 : 1; }

int main() {
	scanf("%d%d", &n, &m);
	preprocess();
	LL ans = 0;
	// for(int i = 1; i <= m; i++)
	// 	for(int j = 1; j <= i; j++)
	// 		printf("A(%d, %d) = %lld, C(%d, %d) = %lld\n", i, j, A(i, j), i, j, C(i, j));
	for(int i = 0; i <= n; i++) {
		ans = (ans + pow_m1(n - i) * C(n, i) % MOD * A(m, n - i) % MOD * A(m - n + i, i) % MOD * A(m - n + i, i) % MOD) % MOD;
		// LL ret = C(n, i) % MOD * A(m, n - i) % MOD * A(m - n + i, i) % MOD * A(m - n + i, i) % MOD * (((n - i) & 1) ? -1 : 1);
		// printf("ans += %lld\n", ret);
	}
	printf("%lld\n", ans);
	return 0;
}