#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int fa[N];
std::vector<int> son[N];

struct SegNode { int t, s; };
SegNode calc(const SegNode &x, const SegNode &y) {
	SegNode z;
	z.s = x.s + y.s;
	z.t = std::max(x.t + y.s, y.t);
	return z;
}
struct SegmentTree {
	SegNode t[N << 2];
	int lazy[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		lazy[x] = -2;
		if(l == r) { t[x].t = t[x].s = -1; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void setlazy(int x, int v, int len) {
		if(v == -2) return;
		t[x].s = len * v, t[x].t = std::max(len * v, v);
		lazy[x] = v;
	}
	void lazydown(int x, int l, int r, int mid) {
		setlazy(x << 1, lazy[x], mid - l + 1), setlazy(x << 1 | 1, lazy[x], r - mid);
		lazy[x] = -2;
	}
	void add(int qind, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("add [%d] %d\n", qind, qv);
		if(l == r) { t[x].t = t[x].s = t[x].s + qv; return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qind <= mid) add(qind, qv, x << 1, l, mid);
		else add(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void set(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("set [%d .. %d] %d\n", ql, qr, qv);
		if(ql <= l && r <= qr) { setlazy(x, qv, r - l + 1); return; }
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(ql <= mid) set(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) set(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegNode query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("query [%d .. %d]\n", ql, qr);
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x, l, r, mid);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
};
struct HeavyLightDecomposition {
	SegmentTree seg;
	int dfn[N], top[N], sz[N], hson[N], dep[N];
	int time_stamp;
	void init() {
		time_stamp = 0;
		dfs1(1), dfs2(1, 1);
		seg.build();
	}
	void dfs1(int u) {
		dep[u] = dep[fa[u]] + 1;
		sz[u] = 1;
		for(int v : son[u]) {
			dfs1(v);
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp) {
		dfn[u] = ++time_stamp;
		top[u] = tp;
		for(int v : son[u]) if(hson[u] == 0 || sz[hson[u]] < sz[v]) hson[u] = v;
		if(hson[u]) dfs2(hson[u], tp);
		for(int v : son[u]) if(v != hson[u]) dfs2(v, v);
	}
	void add(int u, int val) { seg.add(dfn[u], val); }
	void setsub(int u, int val) { seg.set(dfn[u], dfn[u] + sz[u] - 1, val); }
	int query(int u) {
		int ret = -INF, sum = 0;
		for(; u; u = fa[top[u]]) {
			auto p = seg.query(dfn[top[u]], dfn[u]);
			ret = std::max(ret, sum + p.t);
			sum += p.s;
		}
		return ret;
	}
} hld;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].push_back(i);
	hld.init();
	for(int i = 1; i <= m; i++) {
		int t, u;
		scanf("%d%d", &t, &u);
		if(t == 1) hld.add(u, 1);
		else if(t == 2) hld.setsub(u, -1), hld.add(u, -hld.query(u) - 1);
		else puts(hld.query(u) >= 0 ? "black" : "white");
	}
	return 0;
}