#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 998244353;

int n, K;
std::map<LL, LL> f[N];
LL fac[N], invfac[N];

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }
LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) ret = ret * a % MOD; if(!(b >>= 1)) return ret; a = a * a % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL a, LL b) { return fac[a] * invfac[b] % MOD * invfac[a - b] % MOD; }

int main() {
	scanf("%d%d", &n, &K);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[n] = inv(fac[n]);
	for(int i = n - 1; i >= 0; i--) invfac[i] = invfac[i + 1] * (i + 1) % MOD;
	f[0][1] = 1;
	for(int i = 0; i < n; i++)
		for(auto k : f[i])
			for(int j = 1; j <= n - i; j++)
				(f[i + j][lcm(k.first, j)] += k.second * fac[j - 1] % MOD * C(n - i - 1, j - 1) % MOD) %= MOD;
	LL ans = 0;
	for(auto p : f[n]) (ans += qpow(p.first, K) * p.second % MOD) %= MOD;
	printf("%lld\n", ans);
	return 0;
}