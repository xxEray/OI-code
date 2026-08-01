#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 1e9 + 7;

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }

int main() {
	int K;
	scanf("%d", &K);
	printf("%lld\n", (6 * qpow(4, (1LL << K) - 2)) % MOD);
	return 0;
}