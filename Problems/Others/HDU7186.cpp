#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;
typedef unsigned long long ull;

const int SQRT_N = 1e6 + 5;
const int LOG_N = 40 + 2;
const LL MOD = 4179340454199820289;

LL mul(LL x, LL y) { return ((ull)x * y - (ull)((long double)x / MOD * y + 0.5) * MOD + MOD) % MOD; }
// LL qmod(LL x) { return x >= MOD ? x - MOD : x; }
// LL mul(LL x, LL y) { LL ret = 0; while(true) { if(y & 1) ret = qmod(ret + x); if(!(y >>= 1)) return ret; x = qmod(x + x); } }
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = mul(ret, x); if(!(y >>= 1)) return ret; x = mul(x, x); } }

LL inv[LOG_N];
LL g(LL x) { return x; }
LL sumg(LL x) { return mul(mul(x, x + 1), inv[2]); }
LL f(LL p, int c) { return mul(qpow(p, c), inv[c]); }
void preprocess() {
	inv[1] = 1;
	for(int i = 2; i <= 40; i++) inv[i] = mul((MOD - MOD / i), inv[MOD % i]);
}

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
				if(h[p][c]) (ret += dfs(x * prod, i + 1, mul(hh, h[p][c]))) %= MOD;
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
				for(int i = 1; i <= c; i++) power *= p, (h[p][c] += MOD - mul(g(power), h[p][c - i])) %= MOD;
			}
		}
	}
	LL solve(LL n_) { n = n_; return dfs(1, 0, 1); }
};

PowerfulNumber<g, sumg, f> PN;

int main() {
	int T; scanf("%d", &T);
	preprocess();
	PN.init(1e6);
	while(T--) {
		LL n;
		scanf("%lld", &n);
		printf("%lld\n", mul(PN.solve(n), qpow(n, MOD - 2)));
	}
	return 0;
} /*
1
9
*/