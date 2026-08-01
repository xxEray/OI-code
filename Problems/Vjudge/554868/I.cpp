#pragma GCC optimize("Ofast")

#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
struct Node { int l, r; } a[N], b[N];
int fa[N];
std::vector<int> sons[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

int dep[N];
void dfs(int u) {
	for(int v : sons[u]) {
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int go[21][N];
void preprocess() {
	for(int i = 1; i <= n; i++) go[0][i] = fa[i];
	for(int j = 1; j <= 17; j++)
		for(int i = 1; i <= n; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int j = 0; j <= 17; j++) if((dep[u] - dep[v]) >> j & 1) u = go[j][u];
	if(u == v) return u;
	for(int j = 17; j >= 0; j--) if(go[j][u] != go[j][v]) u = go[j][u], v = go[j][v];
	return fa[u];
}

struct DSU {
	int fa[2 * N], sz[2 * N];
	void init() { for(int i = 1; i <= 2 * n; i++) fa[i] = i, sz[i] = 1; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	bool same(int x, int y) { return find(x) == find(y); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if(x == y) return;
		if(sz[x] > sz[y]) std::swap(x, y);
		fa[x] = y, sz[y] += sz[x];
	}
} dsu, tag[21];

void init_dsu() {
	dsu.init();
	for(int i = 0; i <= 17; i++) tag[i].init();
}

LL ans = 1;
void merge(int j, int i1, int i2, int tp) {
	// printf("merge %d^%d %d^%d (%d)\n", i1, j, i2, j, tp);
	if(tag[j].same(i1 + (tp == 2) * n, i2)) return;
	tag[j].merge(i1 + (tp == 2) * n, i2), tag[j].merge(i1 + (tp == 1) * n, i2 + n);
	if(j == 0) {
		if(dsu.same(i1, i2)) return;
		int oi1 = dsu.find(i1), oi2 = dsu.find(i2);
		(ans *= inv(b[oi1].r - b[oi1].l + 1)) %= MOD, (ans *= inv(b[oi2].r - b[oi2].l + 1)) %= MOD;
		dsu.merge(i1, i2);
		int i = dsu.find(i1);
		b[i].l = std::max(b[oi1].l, b[oi2].l), b[i].r = std::min(b[oi1].r, b[oi2].r);
		if(b[i].l > b[i].r) ans = 0;
		else (ans *= b[i].r - b[i].l + 1) %= MOD;
		return;
	}
	if(tp == 1) merge(j - 1, i1, i2, tp), merge(j - 1, go[j - 1][i1], go[j - 1][i2], tp);
	else merge(j - 1, i1, go[j - 1][i2], tp), merge(j - 1, go[j - 1][i1], i2, tp);
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), sons[fa[i]].push_back(i);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r), b[i] = a[i];
	dep[1] = 1, dfs(1), preprocess();
	init_dsu();
	// for(int i = 1; i <= n; i++) printf("%d: fa=%d, dep=%d\n", i, fa[i], dep[i]);
	for(int i = 1; i <= n; i++) (ans *= a[i].r - a[i].l + 1) %= MOD;
	scanf("%d", &Q);
	while(Q--) {
		int u1, v1, u2, v2, f1, f2;
		scanf("%d%d%d%d", &u1, &v1, &u2, &v2);
		f1 = lca(u1, v1), f2 = lca(u2, v2);
		for(int i = 17; i >= 0; i--) if(dep[go[i][u1]] >= dep[f1] && dep[go[i][u2]] >= dep[f2])
			merge(i, u1, u2, 1), u1 = go[i][u1], u2 = go[i][u2];
		merge(0, u1, u2, 1);
		for(int i = 17; i >= 0; i--) if(dep[go[i][v1]] >= dep[f1] && dep[go[i][v2]] >= dep[f2])
			merge(i, v1, v2, 1), v1 = go[i][v1], v2 = go[i][v2];
		merge(0, v1, v2, 1);
		if(dep[u1] < dep[v1]) std::swap(u1, u2), std::swap(v1, v2), std::swap(f1, f2);
		// printf("now merge %d->%d %d->%d\n", u1, v1, u2, v2);
		int d1 = dep[u1] - dep[v1], d2 = dep[v2] - dep[u2];
		int d = 0;
		for(int i = 0; i <= 17; i++) if(d1 >> i & 1) {
			int v = v2;
			for(int j = 0; j <= 17; j++) if((d2 - d - (1 << i) + 1) >> j & 1) v = go[j][v];
			merge(i, u1, v, 2);
			u1 = go[i][u1], d += (1 << i);
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
8
1 2 3 4 5 8 6
3 7
2 6
3 8
5 10
5 8
2 9
3 8
6 8
1
1 3 7 6
*/