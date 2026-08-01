#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
struct SegNode { int lv, rv, t; };
SegNode calc(SegNode x, SegNode y) {
	SegNode z;
	z.lv = x.lv, z.rv = y.rv;
	z.t = x.t + y.t + (x.rv == y.lv);
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int lazy[N << 2];
	void setlazy(int x, int len, int v) {
		if(!v) return;
		lazy[x] = v;
		t[x].lv = t[x].rv = v, t[x].t = len - 1;
	}
	void lazydown(int x, int l, int r, int mid) {
		setlazy(x << 1, mid - l + 1, lazy[x]), setlazy(x << 1 | 1, r - mid, lazy[x]);
		lazy[x] = 0;
	}
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = {0, 0, r - l + 1}, lazy[x] = 0;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("modify [%d, %d] = %d\n", ql, qr, qv);
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) { setlazy(x, r - l + 1, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("query [%d, %d]\n", ql, qr);
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;
struct HeavyLightDecomposition {
	int fa[N], top[N], dfn[N], dep[N], sz[N], hson[N];
	int time_stamp, cnt;
	void init() {
		time_stamp = 0, cnt = 0;
		seg.build();
		fa[1] = 0;
		dfs1(1), dfs2(1, 1);
		assert(time_stamp == n);
		// for(int i = 1; i <= n; i++) printf("%d: top=%d, dfn=%d, hson=%d, dep=%d, sz=%d\n", i, top[i], dfn[i], hson[i], dep[i], sz[i]);
		for(int i = 1; i <= n; i++) seg.modify(dfn[i], dfn[i], ++cnt);
	}
	void dfs1(int u) {
		dep[u] = dep[fa[u]] + 1;
		sz[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dfs1(v);
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp) {
		top[u] = tp;
		dfn[u] = ++time_stamp;
		hson[u] = 0;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u] && (hson[u] == 0 || sz[hson[u]] < sz[edge[i].to])) hson[u] = edge[i].to;
		if(hson[u]) dfs2(hson[u], tp);
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u] && edge[i].to != hson[u]) dfs2(edge[i].to, edge[i].to);
	}
	void modify(int u, int v) {
		// printf("hld: modify %d - %d\n", u, v);
		cnt++;
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
			seg.modify(dfn[top[u]], dfn[u], cnt);
			u = fa[top[u]];
		}
		if(dep[u] < dep[v]) std::swap(u, v);
		seg.modify(dfn[v], dfn[u], cnt);
	}
	int query(int u, int v) {
		// printf("hld: query %d - %d\n", u, v);
		int ret = 0, lastu = 0, lastv = 0;
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v), std::swap(lastu, lastv);
			auto p = seg.query(dfn[top[u]], dfn[u]);
			ret += p.t + (p.rv == lastu), lastu = p.lv;
			u = fa[top[u]];
		}
		if(dep[u] < dep[v]) std::swap(u, v), std::swap(lastu, lastv);
		auto p = seg.query(dfn[v], dfn[u]);
		ret += p.t + (p.lv == lastv) + (p.rv == lastu);
		return ret;
	}
} hld;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		hld.init();
		for(int i = 1; i <= m; i++) {
			int op, u, v;
			scanf("%d%d%d", &op, &u, &v);
			if(op == 1) hld.modify(u, v);
			else printf("%d\n", hld.query(u, v));
		}
	}
	return 0;
} /*
1
7 3
6 2
3 1
1 6
5 3
2 7
1 4
1 5 6
1 5 1
2 4 3
*/