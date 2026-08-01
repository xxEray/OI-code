#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7 + 5;
const LL MOD = 998244353;

int m;
LL k1, k2;

bool isprm[N];
std::vector<int> prime;
int phi[N];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	phi[1] = 1;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), phi[i] = i - 1;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				phi[i * p] = phi[i] * p;
				break;
			} else phi[i * p] = phi[i] * (p - 1);
		}
	}
}

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

inline LL qpow(LL x, LL y, LL mod = MOD) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
inline LL inv(LL x) { return qpow(x, MOD - 2, MOD); }

int main() {
#ifndef DEBUG
	freopen("calculate.in", "r", stdin);
	freopen("calculate.out", "w", stdout);
#endif
	sieve(1e7);
	int T; scanf("%d", &T);
	while(T--) {
		LL a1, b1, a2, b2;
		scanf("%d%lld%lld%lld%lld", &m, &a1, &b1, &a2, &b2);
		k1 = gcd(a1, b1), k2 = gcd(a2, b2);
		LL v;
		if(a1 == 0 || b1 == 0) v = qpow(m, k2 - 1, MOD - 1);
		else v = (qpow(m, k2 - 1, MOD - 1) - qpow(m, k1 - 1, MOD - 1) + MOD - 1) % (MOD - 1);
		std::vector<int> factors;
		for(int i = 1; i * i <= m; i++) if(m % i == 0) {
			factors.emplace_back(i);
			if(i * i != m) factors.emplace_back(m / i);
		}
		LL ans = 0;
		for(int d : factors) (ans += phi[m / d] * qpow(1 - ((m / d & 1) ? -1 : 1), d * v % (MOD - 1)) % MOD) %= MOD;
		printf("%lld\n", ans * inv(m) % MOD);
	}
	return 0;
}