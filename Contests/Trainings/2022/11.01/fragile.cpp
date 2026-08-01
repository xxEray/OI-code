#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 2e5 + 5;

#define SZ(container) ((int)(container).size())

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N], dep[N];
int occur[N], in[N], out[N];
std::vector<int> dfo, eto;
void dfs(int u) {
	dfo.push_back(u), eto.push_back(u);
	occur[u] = SZ(eto) - 1, in[u] = SZ(dfo) - 1;
	dep[u] = dep[fa[u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
		eto.push_back(u);
	}
	out[u] = SZ(dfo) - 1;
}
int lg[N << 1], gomn[N << 1][21], go[N][21];
int minid(int x, int y) { return dep[x] < dep[y] ? x : y; }
void preprocess() {
	lg[0] = -1;
	for(int i = 1; i < SZ(eto); i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i < SZ(eto); i++) gomn[i][0] = eto[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 < SZ(eto); i++)
			gomn[i][j] = minid(gomn[i][j - 1], gomn[i + (1 << (j - 1))][j - 1]);
	for(int i = 1; i <= n; i++) go[i][0] = fa[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[i][j] = go[go[i][j - 1]][j - 1];
}
int lca(int u, int v) {
	int l = occur[u], r = occur[v];
	if(l > r) std::swap(l, r);
	int k = lg[r - l + 1];
	return minid(gomn[l][k], gomn[r - (1 << k) + 1][k]);
}

struct Diameter {
	int x, y;
	Diameter(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	int calc() const { assert(x != -1); return dep[x] + dep[y] - 2 * dep[lca(x, y)] + 1; }
};
bool operator<(Diameter x, Diameter y) { return x.calc() < y.calc(); }
Diameter calc(Diameter x, Diameter y)
	{ return x.x == -1 || y.x == -1 ? (x.x == -1 ? y : x) : std::max({x, y, Diameter(x.x, y.y), Diameter(x.x, y.x), Diameter(x.y, y.x), Diameter(x.y, y.y)}); }
struct SegmentTree {
	Diameter t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = Diameter(dfo[l], dfo[l]); return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	Diameter query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return Diameter(-1, -1);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("fragile.in", "r", stdin);
	freopen("fragile.out", "w", stdout);
#endif
	dfo.push_back(0), eto.push_back(0); // 1-indexed now
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1);
	preprocess();
	seg.build();
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		int dia;
		if(x == y) {
			// puts("Type 1");
			dia = seg.query(1, n).calc();
		} else if(in[y] <= in[x] && out[x] <= out[y]) { // x is in the subtree of y
			// puts("Type 2");
			int u = x, d = dep[x] - dep[y] - 1;
			for(int i = 0; i <= 20; i++) if(d >> i & 1) u = go[u][i];
			dia = calc(seg.query(1, in[u] - 1), seg.query(out[u] + 1, n)).calc();
		} else { // x is not in the subtree of y
			// puts("Type 3");
			dia = seg.query(in[y], out[y]).calc();
		}
		// printf("%d\n", dia);
		puts(dia % 3 == 2 ? "Yohane" : "Riko");
	}
	return 0;
} /*
8 8
8 1
2 7
5 3
5 6
7 1
1 6
5 4
7 7
3 2
3 1
5 7
3 8
5 3
6 4
3 4

*/