#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 998244353;

int K;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0LL : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

LL f(LL n, LL m) {
	auto calc = [&](LL k) -> LL {
		LL sum = 0;
		for(int i = 0; i * (K + 1) <= k; i++) {
			int j = k - i * (K + 1);
			(sum += ((i & 1) ? MOD - 1 : 1) * C(n - m - 1, i) % MOD * C(n - m + j, j)) %= MOD;
		}
		return sum;
	};
	return (calc(m) + (K + 1) * calc(m - K - 2) % MOD + MOD - (K + 2) * calc(m - K - 1) % MOD) % MOD;
}

std::vector<int> prime;
bool isprm[N];
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

int main() {
#ifndef DEBUG
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
#endif
	get_factorial(1e6);
	sieve(1e6);
	int T; scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d%d", &n, &m, &K);
		LL ans = 0;
		int g = gcd(n, m);
		for(int d = 1; d <= g; d++) if(g % d == 0) (ans += f(n / d, m / d) * phi[d]) %= MOD;
		printf("%lld\n", ans * inv(n) % MOD);
	}
	return 0;
} /*
5
7 3 2
6 3 2
5 3 2
4 3 2
19 5 4
*/