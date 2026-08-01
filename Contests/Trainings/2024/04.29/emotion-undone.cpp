#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct Path { int u, v; LL w; };
std::vector<Path> path[N];

int fa[N], dfn[N], sz[N], dep[N];
int time_stamp;
void predfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		predfs(v);
		sz[u] += sz[v];
	}
}
int go[21][N];
int lower_dep(int u, int v) { return dep[u] < dep[v] ? u : v; }
void binary_lifting() {
	for(int i = 1; i <= n; i++) go[0][dfn[i]] = i;
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = lower_dep(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
	if(u == v) return u;
	int l = dfn[u], r = dfn[v];
	if(l > r) std::swap(l, r);
	int k = 31 ^ __builtin_clz(r - l);
	return fa[lower_dep(go[k][l + 1], go[k][r - (1 << k) + 1])];
}

struct BIT {
	LL t[N];
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bit;

struct SegmentTree {
	int mx;
	LL t[N << 2];
	void build() { for(mx = 1; mx <= n; mx <<= 1); }
	void modify(int x, LL v) {
		x += mx, t[x] = v;
		for(x >>= 1; x; x >>= 1) t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	LL query(int l, int r) {
		LL ret = 0;
		for(l += mx - 1, r += mx + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::max(ret, t[l ^ 1]);
			if(r & 1) ret = std::max(ret, t[r ^ 1]);
		}
		return ret;
	}
} seg;

LL g[N], h[N], f[N], sum[N];
void dfs_g(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		dfs_g(v);
	}
	for(auto [x, y, w] : path[u]) g[u] = std::max(g[u], w - bit.query(dfn[x]) - bit.query(dfn[y]) + 2 * bit.query(dfn[u]));
}

void dfs_h(int u) {
	if(fa[u]) {

	}
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) dfs_h(edge[i].to);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	predfs(1);
	binary_lifting();
	seg.build();
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); path[lca(u, v)].push_back({u, v, w}); }
	
	return 0;
}