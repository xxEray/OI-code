#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, m, K;

int ind[N];

int cnt[2];

LL fac[N], invfac[N];
LL qpow(LL x, LL y, LL mod = MOD) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod = MOD) { return qpow(x, mod - 2, mod); }
LL C(int x, int y, LL mod = MOD) { return x < y ? 0 : fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx, LL mod = MOD) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx], mod);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}


int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); ind[u]++, ind[v]++; }
	for(int i = 1; i <= n; i++) cnt[ind[i] % 2]++;
	get_factorial(n);
	LL ans = 0;
	for(int i = 0; i <= std::min(K, cnt[1]); i += 2) (ans += C(cnt[1], i) * C(cnt[0], K - i)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}