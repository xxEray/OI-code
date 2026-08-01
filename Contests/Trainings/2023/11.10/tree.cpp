#ifndef DEBUG
	#pragma GCC optimize("Ofast", "inline", "-ffast-math")
	#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#endif

#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

int n;
struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], ek;
	void add_edge(int u, int v) { /* printf("%d -> %d\n", u, v);  */edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
	Graph() : ek(1) {}
} G, Tr;

int fa[N], dep[N];
int dfn[N], dfl[N], time_stamp;
void dfs(int u) {
	dfn[u] = ++time_stamp, dfl[dfn[u]] = u;
	dep[u] = dep[fa[u]] + 1;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) if(G.edge[i].to != fa[u]) {
		int v = G.edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}
int calc(int x, int y) { return dep[x] < dep[y] ? x : y; }
int go[20][N];
void binary_lifting() {
	for(int i = 1; i <= n; i++) go[0][i] = dfl[i];
	for(int j = 1; j <= 19; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = calc(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
	if(u == v) return u;
	int l = dfn[u], r = dfn[v];
	if(l > r) std::swap(l, r);
	int k = (31 ^ __builtin_clz(r - l));
	return fa[calc(go[k][l + 1], go[k][r - (1 << k) + 1])];
}

bool isprm[N];
int phi[N];
std::vector<int> prime;
void sieve(int mx) {
	phi[1] = 1;
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), phi[i] = i - 1;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				phi[p * i] = phi[i] * p;
				break;
			} else phi[p * i] = phi[p] * phi[i];
		}
	}
	// for(int i = 1; i <= mx; i++) printf("phi[%d] = %d\n", i, phi[i]);
}

int val;

typedef unsigned long long ull;
struct Barret {
    unsigned m, p;
    void init(int pp) { m = ((ull)1 << 32) / pp; p = pp; }
    int operator()(int x) {
		unsigned w = x - (((ull)x * m) >> 32) * p;
		if(w >= p) w -= p;
		// if(w != x % p) printf(">> %lld, %lld %lld\n", w, x, p);
		return w;
	}
} barret;

bool ok[N];
int tin[N];
int sz[N], depth[N];
inline int mod(const int &x) { return x >= val ? x - val : x; }
LL ret;
void dfs2(int u) {
	sz[u] = 1;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) {
		int v = Tr.edge[i].to;
		dfs2(v);
		sz[u] += sz[v];
	}
}
void dfsclear(int u) {
	tin[depth[u]] = 0;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) dfsclear(Tr.edge[i].to);
}
int base;
void dfsiterate(int u) {
	if(ok[u]) ret += tin[mod(base - depth[u] + val)];
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) dfsiterate(Tr.edge[i].to);
}
void dfstag(int u) {
	if(ok[u]) tin[depth[u]]++;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) dfstag(Tr.edge[i].to);
}
void dfs3(int u) {
	int hson = 0;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(!hson || sz[Tr.edge[i].to] > sz[hson]) hson = Tr.edge[i].to;
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) if(Tr.edge[i].to != hson) {
		int v = Tr.edge[i].to;
		dfs3(v);
		dfsclear(v);
	}
	if(hson) dfs3(hson);
	// int oldret = ret;
	if(ok[u]) ret += tin[depth[u]], tin[depth[u]]++;
	base = mod(2 * depth[u]);
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) {
		int v = Tr.edge[i].to;
		if(v != hson) dfsiterate(v), dfstag(v);
	}
	// if(ret - oldret) printf("iterate %d - %d: %lld\n", u, hson, ret - oldret);
}

std::vector<int> multiple[N];
void get_multiple() {
	std::vector<int> vct;
	for(int i = 1; i <= n; i++) vct.emplace_back(i);
	std::sort(vct.begin(), vct.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
	for(int x : vct) for(int i = 1; i * i <= x; i++) if(x % i == 0) {
		multiple[i].push_back(x);
		if(i * i != x) multiple[x / i].push_back(x);
	}
}

std::vector<int> stk;
LL calc(int v) {
	if(v == 1) return (LL)n * n;
	val = v;
	barret.init(v);
	Tr.ek = 1;
	stk.clear();
	stk.emplace_back(1);
	Tr.head[1] = 0, depth[1] = barret(dep[1]);
	for(int u : multiple[v]) {
		int l = lca(u, stk.back());
		if(stk.back() != l) {
			while(dfn[l] < dfn[stk.end()[-2]]) Tr.add_edge(stk.end()[-2], stk.back()), stk.pop_back();
			if(stk.end()[-2] != l) Tr.head[l] = 0, depth[l] = barret(dep[l]), Tr.add_edge(l, stk.back()), stk.back() = l;
			else Tr.add_edge(l, stk.back()), stk.pop_back();
		}
		Tr.head[u] = 0, depth[u] = barret(dep[u]), stk.push_back(u);
	}
	while(stk.size() >= 2) Tr.add_edge(stk.end()[-2], stk.back()), stk.pop_back();
	ret = 0;
	for(int i = v; i <= n; i += v) ok[i] = true;
	dfs2(1), dfs3(1), dfsclear(1);
	for(int i = v; i <= n; i += v) ok[i] = false;
	// printf("calc %d = %lld\n", v, 2 * ret + n / v);
	return 2 * ret + n / v;
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); G.add_edge(u, v), G.add_edge(v, u); }
	dfs(1), binary_lifting();
	sieve(n);
	get_multiple();
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans += calc(i) * phi[i];
	printf("%lld\n", ans);
	return 0;
} /*
10
1 2
1 3
1 4
2 5
5 6
3 7
4 8
2 9
8 10
*/