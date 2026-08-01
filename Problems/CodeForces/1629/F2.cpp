#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const int MAXN = 1e6;
const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

LL fac[N], invfac[N];

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }
LL C(LL a, LL b) { return a < b ? 0 : fac[a] * invfac[b] % MOD * invfac[a - b] % MOD; }

LL f(int n, int m, LL K) {
	LL ans = 0;
	if(m == 0) return n * K % MOD;
	for(int i = 1; i < n; i++) (ans += i * K % MOD * C(n - i - 1, m - 1) % MOD * qpow(inv2, n - i) % MOD) %= MOD;
	return ans;
}

int main() {
	fac[0] = 1;
	for(int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[MAXN] = qpow(fac[MAXN], MOD - 2);
	for(int i = MAXN; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	int T; scanf("%d", &T);
	while(T--) {
		int n, m; LL K;
		scanf("%d%d%lld", &n, &m, &K);
		printf("%lld\n", f(n, n - m, K));
	}
	return 0;
}