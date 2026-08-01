#include <bits/stdc++.h>

typedef long long LL;

const int N = 1.01e5 + 5;
const int MAXS = (1 << 18) + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int n, m;
int e[100][2];

int fa[N], sz[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] > sz[y]) std::swap(x, y);
	sz[y] += sz[x], fa[x] = y;
}

int d[N], bc[N];

LL f[100][100], g[MAXS];

int main() {
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("ghaph.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &e[i][0], &e[i][1]);
	get_factorial(n + 2 * m);
	for(int i = 0; i <= m; i++) for(int j = 0; j <= 2 * m; j++) {
		for(int k = 0; k <= n - j; k++) (f[i][j] += C(n - j, k) * (i + k - 1 >= 0 ? fac[i + k - 1] : 0) % MOD) %= MOD;
	}
	int U = (1 << m) - 1;
	for(int s = 0; s <= U; s++) {
		int tot = __builtin_popcount(s);
		LL ret = 0;
		bool flag = true;
		std::vector<int> dots;
		// get dots
		for(int i = 1; i <= m; i++) if(s >> (i - 1) & 1) dots.push_back(e[i][0]), dots.push_back(e[i][1]);
		std::sort(dots.begin(), dots.end()), dots.erase(std::unique(dots.begin(), dots.end()), dots.end());
		// init
		for(int u : dots) fa[u] = u, sz[u] = 1, d[u] = 0, bc[u] = 0;
		// process edges
		for(int i = 1; i <= m; i++) if(s >> (i - 1) & 1) merge(e[i][0], e[i][1]), d[e[i][0]]++, d[e[i][1]]++;
		// check d
		for(int u : dots) if(d[u] >= 3) flag = false;
		// calculate cnt
		int cnt[4] = {};
		for(int u : dots) if(find(u) == u) cnt[std::min(sz[u], 3)]++;
		cnt[1] = n - dots.size();
		// calculate bc
		for(int u : dots) if(d[u] == 1) bc[find(u)]++;
		// calculate cycle
		int cycle = 0, szcycle = 0;
		for(int u : dots) if(find(u) == u && bc[u] == 0) cycle++, szcycle = sz[u];
		if(cycle > 1) flag = false;
		else if(cycle == 1) ret = (szcycle == (int)dots.size());
		else {
			int kmin = std::max(3 - cnt[3] * 3 - cnt[2] * 2, 0);
			LL val = f[cnt[2] + cnt[3]][dots.size()];
			for(int k = 0; k < kmin; k++) (val += MOD - C(cnt[1], k) * (cnt[2] + cnt[3] + k - 1 >= 0 ? fac[cnt[2] + cnt[3] + k - 1] : 0) % MOD) %= MOD;
			(ret += (1 << (cnt[2] + cnt[3])) % MOD * inv2 % MOD * val % MOD) %= MOD;
		}
		// printf("%d: ret = %lld\n", s, ret);
		g[s] = flag * (((tot & 1) ? MOD - 1 : 1) * ret % MOD);
	}
	for(int i = 1; i <= m; i++) {
		LL ans = 0;
		for(int s = 0; s < (1 << i); s++) (ans += g[s]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
9 7
1 2
2 3
3 1
4 5
5 6
6 4
1 6
*/