#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;
const LL MOD = 998244353;

LL f[N], g[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	f[0] = 1, f[1] = 2, g[1] = 2;
	for(int i = 2; i <= 2000000; i++) f[i] = (f[i - 1] + f[i - 2]) % MOD, g[i] = g[i - 2] * f[i] % MOD;
	int T; scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%lld\n", qpow(g[2 * std::min(n, m) - 1], 2) * qpow(f[2 * std::min(n, m)], std::abs(n - m)) % MOD);
	}
	return 0;
}