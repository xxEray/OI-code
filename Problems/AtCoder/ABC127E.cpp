#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

LL n, m, K;

LL fac[N];
LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return fac[x] * inv(fac[y]) % MOD * inv(fac[x - y]) % MOD; }

int main() {
	scanf("%lld%lld%lld", &n, &m, &K);
	LL mx = std::max(n * m, K);
	fac[0] = 1;
	for(LL i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	LL ans = 0;
	for(LL i = 1; i <= n; i++) for(LL j = 1; j <= m; j++) {
		// #1 正 L 字型  |_
		(ans += ((i - 1) * (j - 1)) * (m - j) % MOD) %= MOD;
		(ans += (i - 1) * ((n - i) * (m - j)) % MOD) %= MOD;
		(ans += (i - 1) * (m - j)) %= MOD;
		// #2 反 L 字型  _|
		(ans += ((i - 1) * (m - j)) * (j - 1) % MOD) %= MOD;
		(ans += (i - 1) * ((n - i) * (j - 1)) % MOD) %= MOD;
		(ans += (i - 1) * (j - 1)) %= MOD;
		// #3 链型 - 或 |
		(ans += (i - 1) * (n - i)) %= MOD;
		(ans += (j - 1) * (m - j)) %= MOD;
		// #4 节点 .
		(ans += i - 1) %= MOD;
		(ans += j - 1) %= MOD;
		(ans += (i - 1) * (j - 1)) %= MOD;
		(ans += (i - 1) * (m - j)) %= MOD;
		// printf("ans = %lld\n", ans);
	}
	(ans *= C(n * m - 2, K - 2)) %= MOD;
	printf("%lld\n", ans);
	return 0;
}