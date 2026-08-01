#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const LL MOD = 998244353;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(int x, int y) { return x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int D;

struct Edge { int u, v, w; } edges[M];
bool operator<(Edge x, Edge y) { return x.w < y.w; }

struct DSU {
	int fa[N];
	void init(int n) { for(int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu;

int bl[N];

std::vector<Edge> vcte[N];
std::vector<int> vctdots[N];

inline LL sum(int x) { return (LL)(x + 1) * x / 2 % MOD; }

LL vf[N], vg[N];
void solve(int major) {
	auto &e = vcte[major];
	auto &dots = vctdots[major];
	auto &f = vf[major], &g = vg[major];
	int n = dots.size(), m = e.size();
	std::sort(e.begin(), e.end());
	e.push_back({0, 0, D + 1});
	int cnt = n;
	(f += C(e[0].w - 1, cnt) * fac[cnt] % MOD) %= MOD, (g += C(e[0].w - 2, cnt - 1) * fac[cnt - 1] % MOD * sum(e[0].w - 1) % MOD) %= MOD;
	for(int i = 0; i < m;) {
		int val = e[i].w;
		while(i < m && e[i].w == val) {
			if(dsu.find(e[i].u) != dsu.find(e[i].v)) cnt--, dsu.merge(e[i].u, e[i].v);
			i++;
		}
		(f += C(e[i].w - 1, cnt) * fac[cnt] % MOD) %= MOD, (g += C(e[i].w - 2, cnt - 1) * fac[cnt - 1] % MOD * sum(e[i].w - 1) % MOD) %= MOD;
	}
}

int main() {
	int n, m;
	scanf("%d%d%d", &n, &m, &D);
	dsu.init(n);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w), dsu.merge(edges[i].u, edges[i].v);
	get_factorial(n);
	for(int i = 1; i <= n; i++) bl[i] = dsu.find(i);
	for(int i = 1; i <= m; i++) vcte[bl[edges[i].u]].push_back(edges[i]);
	for(int i = 1; i <= n; i++) vctdots[bl[i]].push_back(i);
	dsu.init(n);
	LL ans = 1;
	for(int i = 1; i <= n; i++) if(bl[i] == i) solve(i), (ans *= (i == bl[1] ? vg[i] : vf[i])) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
3 5 2
1 2 1
1 2 2
1 2 2
1 2 1
2 3 2
*/