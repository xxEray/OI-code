#include <bits/stdc++.h>

typedef long long LL;

const LL MOD = 998244353;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

namespace Solve_1_6 { // n <= 20, m <= 50
	const int N = 20 + 3;
	const int MAXS = (1 << 20) + 5;
	LL f[MAXS];
	std::vector<std::pair<int, int>> to[N];
	void main() {
		for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); to[u].emplace_back(v, w); }
		int U = (1 << n) - 1;
		for(int s = 0; s <= U; s++) f[s] = LLINF;
		f[U] = 0;
		for(int s = U - 1; s >= 0; s--)
			for(int u = 1; u <= n; u++) if(~s >> (u - 1) & 1) {
				int mn = INF;
				for(auto [v, w] : to[u]) if(s >> (v - 1) & 1) mn = std::min(mn, w);
				if(mn < INF) f[s] = std::min(f[s], f[s | (1 << (u - 1))] + mn);
			}
		int cnt = 0;
		LL sum = 0;
		for(int s = 0; s <= U; s++) if(__builtin_popcount(s) == K) {
			if(f[s] == LLINF) { cnt = -1; break; }
			cnt++, (sum += f[s]) %= MOD;
		}
		if(cnt == -1) puts("-1");
		else printf("%lld\n", sum * inv(cnt) % MOD);
	}
}

namespace Solve_8 { // n = K
	void main() {
		puts("0");
	}
}

namespace Solve_9 { // n - 1 = K
	const int N = 1e5 + 5;
	int mn[N];
	void main() {
		for(int i = 1; i <= n; i++) mn[i] = INF;
		for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); mn[u] = std::min(mn[u], w); }
		LL sum = 0;
		for(int i = 1; i <= n; i++)
			if(mn[i] == INF) { sum = -1; break; }
			else sum += mn[i];
		if(sum == -1) puts("-1");
		else printf("%lld\n", sum * inv(n) % MOD);
	}
}

namespace Solve_10_11 { // n = m
	const int N = 1e5 + 5;
	int to[N];
	int ind[N], oud[N];
	void main() {
		LL sum = 0;
		for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); ind[v]++, oud[u]++; to[u] = v; sum += w; }
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= (ind[i] == 1 && oud[i] == 1);
		int cnt = 1;
		for(int i = to[1]; i != 1; i = to[i]) cnt++;
		flag &= (cnt == n);
		if(flag) printf("%lld\n", sum * (n - K) % MOD * inv(n) % MOD);
		else puts("-1");
	}
}

int main() {
#ifndef DEBUG
	freopen("station.in", "r", stdin);
	freopen("station.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	if(n <= 20 && m <= 50) Solve_1_6::main();
	else if(n == K) Solve_8::main();
	else if(K == n - 1) Solve_9::main();
	else if(n == m) Solve_10_11::main();
	return 0;
}