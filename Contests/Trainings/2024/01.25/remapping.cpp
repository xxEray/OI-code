#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;
typedef unsigned long long ull;

const int SQRT_N = 1e7 + 5;

LL MOD;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

LL pow2[100];
void preprocess() {
	pow2[0] = 1;
	for(int i = 1; i < 100; i++) pow2[i] = pow2[i - 1] * 2 % MOD;
}

LL g(LL x) { return 1; }
LL sumg(LL x) { return x % MOD; }
LL f(LL p, int c) { return pow2[c]; }

// g(x): return g(x)
// sumg(x): return \sum g(i)
// f(p, c): return f(p^c)
template<LL (*g)(LL), LL (*sumg)(LL), LL (*f)(LL, int)>
struct PowerfulNumber {
private:
	LL n;
	LL h[SQRT_N][LOG_N];
	bool isprm[SQRT_N];
	std::vector<LL> prime;
	LL dfs(LL x, int t, LL hh) {
		LL ret = mul(hh, sumg(n / x));
		for(int i = t; i < (int)prime.size(); i++) {
			LL p = prime[i];
			if(x > n / p / p) break;
			LL prod = p;
			for(int c = 2; ; c++) {
				if(x * prod > n / p) break;
				prod *= p;
				if(h[p][c]) (ret += dfs(x * prod, i + 1, hh * h[p][c] % MOD)) %= MOD;
			}
		}
		return ret;
	}
public:
	void init(int sqrt_n) {
		prime.clear(), prime.shrink_to_fit();
		for(int i = 2; i <= sqrt_n; i++) isprm[i] = true;
		for(int i = 2; i <= sqrt_n; i++) {
			if(isprm[i]) prime.push_back(i);
			for(LL p : prime) {
				if(i * p > sqrt_n) break;
				isprm[i * p] = false;
				if(i % p == 0) break;
			}
		}
		for(LL p : prime) {
			LL prod = 1;
			h[p][0] = 1;
			for(int c = 1; ; c++) {
				prod *= p;
				if(prod > (LL)sqrt_n * sqrt_n) break;
				h[p][c] = f(p, c);
				LL power = 1;
				for(int i = 1; i <= c; i++) power *= p, (h[p][c] += MOD - g(power) * h[p][c - i] % MOD) %= MOD;
			}
		}
	}
	LL solve(LL n_) { n = n_; return dfs(1, 0, 1); }
};

PowerfulNumber<g, sumg, f> PN;

int main() {
	preprocess();
	LL n;
	scanf("%lld%lld", &n, &MOD);
	PN.init(1e7);
	printf("%lld\n", PN.solve(n));
	return 0;
} /*
1
9
*/