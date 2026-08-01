#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 1e9 + 7;

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL n, K;
		scanf("%lld%lld", &n, &K);
		LL ans = 0;
		for(int i = 0; i < 64; i++) if(K & (1LL << i)) (ans += qpow(n, i)) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}