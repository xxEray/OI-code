#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

typedef long long LL;
const LL MOD = 1e9 + 7;

int n, K;

std::vector<int> d;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

std::map<LL, LL> f;

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; (LL)i * i <= n; i++) if(n % i == 0) d.push_back(i), i != n / i ? d.push_back(n / i) : (void)0;
	std::sort(d.begin(), d.end());
	LL ans = 0;
	for(int i : d) {
		(f[i] += qpow(K, (i + 1) / 2)) %= MOD;
		for(int j : d) {
			if((LL)j * j > i) break;
			if(i % j) continue;
			if(i != 1) (f[i] += MOD - f[j]) %= MOD;
			if(j != i / j && j != 1) (f[i] += MOD - f[i / j]) %= MOD;
		}
		// printf("%d: %lld\n", i, f[i]);
		(ans += f[i] * ((i & 1) ? i : (i >> 1)) % MOD) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}