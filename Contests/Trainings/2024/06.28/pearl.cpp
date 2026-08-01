#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 5;
const LL MOD = 1e9 + 7;

int n, K;
char s[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

namespace Solve_n22 {
	void main() {
		int base = 0;
		for(int i = 1; i <= K; i++) base |= (s[i] - '0') << (i - 1);
		std::set<int> st;
		int U = (1 << (n - K)) - 1;
		for(int s = 0; s <= U; s++) {
			int t = s << K | base;
			int val = t;
			for(int i = 0; i < n; i++) {
				t = (t << 1 | (t >> (n - 1) & 1)) & ((1 << n) - 1);
				val = std::min(val, t);
			}
			int t2 = 0;
			for(int i = 0; i < n; i++) t2 |= (t >> i & 1) << (n - i - 1);
			t = t2;
			for(int i = 0; i < n; i++) {
				t = (t << 1 | (t >> (n - 1) & 1)) & ((1 << n) - 1);
				val = std::min(val, t);
			}
			st.emplace(val);
			// printf("%d: %d\n", s, val);
		}
		printf("%d\n", (int)st.size());
	}
}

namespace Solve_K1 {
	const int N = 1e5 + 5;
	int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
	LL f[N];
	LL power2[N] = {1};
	int fa[N];
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
	void main() {
		for(int i = 1; i <= n; i++) power2[i] = power2[i - 1] * 2 % MOD;
		LL ans = 0;
		auto solve1 = [&](int g) {
			for(int i = 0; i < n; i++) fa[i] = i;
			for(int i = 0; i < n; i++) merge(i, (i + g) % n);
			int cnt = 0;
			for(int i = 0; i < n; i++) cnt += find(i) == i;
			return power2[cnt];
		};
		auto solve2 = [&](int g) {
			for(int i = 0; i < n; i++) fa[i] = i;
			for(int i = 0; i < n; i++) merge(i, ((n - i - 1) + g + n) % n);
			int cnt = 0;
			for(int i = 0; i < n; i++) cnt += find(i) == i;
			return power2[cnt];
		};
		for(int i = 1; i <= n; i++) if(n % i == 0) f[i] = solve1(i) + solve2(i);
		for(int i = 1; i <= n; i++) (ans += f[gcd(i, n)]) %= MOD;
		// printf("ans = %lld\n", ans);
		printf("%lld\n", (ans * inv(2 * n) % MOD + MOD - 1) % MOD);
	}
}

int main() {
#ifndef DEBUG
	freopen("pearl.in", "r", stdin);
	freopen("pearl.out", "w", stdout);
#endif
	scanf("%d%d%s", &n, &K, s + 1);
	if(n <= 22) Solve_n22::main();
	else if(K == 1) Solve_K1::main();
	return 0;
} /*
2 1
1
*/