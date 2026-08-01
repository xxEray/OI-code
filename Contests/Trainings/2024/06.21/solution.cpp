#include <bits/stdc++.h>

typedef long long LL;
typedef __int128_t LLL;

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = (LLL)ret * x % mod; if(!(y >>= 1)) return ret; x = (LLL)x * x % mod; } }

LL rand(LL l, LL r) {
	static std::mt19937 mt(std::random_device{}());
	return std::uniform_int_distribution<LL>{l, r}(mt);
}

const LL miller[] = {2, 3, 5, 7, 11, 13, 17, 19, 31, 37};
bool miller_rabin(LL n) {
	LL u = n - 1;
	int t = 0;
	while(~u & 1) t++, u >>= 1;
	for(LL a : miller) {
		a %= n;
		LL v = qpow(a, u, n);
		if(v == 0 || v == 1) continue;
		for(int _ = 1; _ <= t && v != n - 1; _++) v = (LLL)v * v % n;
		if(v != n - 1) return /* printf("%lld is not a prime (a=%lld)\n", n, a),  */false;
	}
	// printf("%lld is a prime\n", n);
	return true;
}
LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL pollard_rho(LL n) {
	LL c = rand(1, n - 1);
	auto f = [&](LL x) -> LL { return ((LLL)x * x + c) % n; };
	LL p = f(0), q = f(f(0));
	while(p != q) {
		LL d = gcd(std::abs(p - q), n);
		if(d > 1) return /* printf("pollard_rho(%lld) = %lld (c=%lld)\n", n, d, c),  */d;
		p = f(p), q = f(f(q));
	}
	// printf("pollard_rho(%lld) failed (c=%lld)\n", n, c);
	return n;
}
std::unordered_map<LL, int> factor;
std::vector<std::pair<LL, int>> vct;
void factorize(LL n) {
	if(n <= 1) return;
	if(miller_rabin(n)) { factor[n]++; return; }
	LL x;
	do { x = pollard_rho(n); } while(x == n);
	factorize(x), factorize(n / x);
}

int main() {
#ifndef DEBUG
	freopen("solution.in", "r", stdin);
	freopen("solution.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		LL n, m;
		scanf("%lld%lld", &n, &m);
		int q = __builtin_ctzll(n);
		LL tn = n >> q;
		LL ans = (1LL << 60);
		auto solve = [&](LL x) {
			if(x > m) return;
			// printf("x = %lld\n", x);
			LL t = m / x;
			int p = 63 ^ __builtin_clzll(t);
			x <<= p;
			ans = std::min(ans, m - x + std::max(p - q, 0));
		};
		factor.clear();
		factorize(tn);
		vct.clear();
		for(auto [p, c] : factor) vct.emplace_back(p, c); // , printf("%lld^%d\n", p, c);
		std::function<void(int, LL)> dfs = [&](int id, LL v) {
			if(id == (int)factor.size()) { solve(v); return; }
			for(int i = 0; i <= vct[id].second; i++) dfs(id + 1, v), v *= vct[id].first;
		};
		dfs(0, 1);
		printf("%lld\n", ans);
	}
	return 0;
} /*
5
1 1
81 721
289 1
209 501
273 831

*/