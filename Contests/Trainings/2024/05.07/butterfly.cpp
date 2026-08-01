#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL mod;

bool isprm[N];
std::vector<int> prime;
int mu[N];
void sieve() {
	mu[1] = 1;
	for(int i = 2; i <= 100000; i++) isprm[i] = true;
	for(int i = 2; i <= 100000; i++) {
		if(isprm[i]) prime.emplace_back(i), mu[i] = -1;
		for(int p : prime) {
			if((LL)p * i > 100000) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				mu[i * p] = 0;
				break;
			} else mu[i * p] = -mu[i];
		}
	}
}

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial() {
	fac[0] = 1;
	for(int i = 1; i <= 100000; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[100000] = inv(fac[100000]);
	for(int i = 100000; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL powern[N];
LL f[N], g[N], h[N];
LL calc(std::function<LL(int)> func, bool type) {
	LL ret = 0;
	for(int i = 1; i <= n; i++) (ret += func(i) * (type ? i - 1 : i) % mod * ((LL)n * (n - 1) / 2 % mod) % mod) %= mod;
	// for(int i = 1; i <= n; i++) {
	// 	LL sum = 0;
	// 	for(int j = 1; j <= n; j++) (sum += i / std::__gcd(i, j)) %= mod;
	// 	(ret += sum * func(i)) %= mod;
	// 	// printf("i = %d, ret = %lld\n", i, ret);
	// }
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j += i) (ret += h[i] * (LL)(n / i) % mod * func(j) % mod * j % mod) %= mod;
	if(type) for(int i = 1; i <= n; i++) (ret += mod - func(i) * n % mod) %= mod;
	return ret;
}

int main() {
	scanf("%d%lld", &n, &mod);
	sieve(), get_factorial();
	powern[0] = 1;
	for(int i = 1; i <= n; i++) powern[i] = powern[i - 1] * n % mod;
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j += i) (h[j] += (mod + mu[j / i]) * inv(i)) %= mod;
	LL ans = 0;
	// u on cycle, v on cycle
	(ans += calc([](int i) { return C(n, i) * fac[i - 1] % mod * i % mod * powern[n - i] % mod; }, true)) %= mod;
	// printf("ans = %lld\n", ans);
	// u on chain, v on cycle
	for(int i = 1; i <= n; i++) f[i] = C(n, i) * fac[i] % mod * powern[n - i] % mod, g[i] = f[i] * i % mod;
	for(int i = n - 1; i >= 1; i--) (f[i] += f[i + 1]) %= mod, (g[i] += g[i + 1]) %= mod;
	(ans += calc([](int i) { return f[i + 1]; }, false)) %= mod;
	// printf("ans = %lld\n", ans);
	// u on chain, v on chain
	for(int i = 2; i <= n; i++) {
		LL sum = 0;
		for(int L = 1; L <= n; L = (i - 1) / ((i - 1) / L) + 1) {
			if((i - 1) / L == 0) break;
			LL len = (i - 1) / ((i - 1) / L) - L + 1;
			// printf("%d / [%d .. %d] are the same. (len = %lld)\n", i - 1, L, (i - 1) / ((i - 1) / L), len);
			(sum += n * len % mod - (i - 2) / ((i - 1) / L) * len % mod + mod) %= mod;
		}
		// for(int L = 1; L <= n; L++) if((i - 1) / L) (sum += mod - (i - 2) / ((i - 1) / L)) %= mod;
		// printf("i = %d, sum = %lld\n", i - 1, sum);
		(ans += (g[i + 1] - f[i + 1] * i % mod + mod) * sum) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
} /*
13 998244353
349413543
*/