#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL K;

LL f[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int main() {
	freopen("spainting.in", "r", stdin);
	freopen("spainting.out", "w", stdout);
	scanf("%d%lld%d", &n, &K, &m);
	for(int i = 1; i < m; i++) f[i] = K;
	LL sum = 0;
	for(int i = 2; i <= n; i++) {
		(sum += f[i - 1]) %= MOD;
		if(i >= m) (sum += MOD - f[i - m]) %= MOD;
		f[i] += sum * (K - 1) % MOD;
	}
	printf("%lld\n", (qpow(K, n) - f[n] + MOD) % MOD);
	return 0;
}