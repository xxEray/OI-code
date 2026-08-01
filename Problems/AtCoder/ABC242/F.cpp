#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 998244353;

LL n, m, B, W, A;

LL fac[N * N], invfac[N * N];
LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) (ret *= a) %= MOD; if(!(b >>= 1)) return ret; (a *= a) %= MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
LL g(int r, int c, int t) { return C(r * c, t); }
LL f(int r, int c, int t) { return g(r, c, t) - g(r, c - 1, t) - g(r - 1, c, t) + g(r - 1, c - 1, t); }

int main() {
	scanf("%lld%lld%lld%lld", &n, &m, &B, &W);
	fac[0] = 1;
	for(int i = 1; i <= n * m; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[n * m] = inv(fac[n * m]);
	for(int i = n * m; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	printf("f(3, 3, 3) = %lld\n", f(3, 3, 3));
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) (ans += C(n, i) * C(m, j) % MOD * f(i, j, W) % MOD * g(n - i, m - j, B) % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}