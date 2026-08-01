#include <cstdio>
#include <algorithm>
#include <assert.h>

const int N = 2e5 + 5;
const int M = 3e5 + 5;
const int QMAX = 5e5 + 5;

int a[N];
struct GraphEdge { int u, v, del; } edge[M];
struct Query { int u, e; } q[QMAX];
int n, m, Q;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

struct Tree {
	std::vector<int> sons[M];
	int head[N], fa[N];
	void add_son(int u, int v) { sons[u].push_back(v), fa[v] = u; }
} Tr;
int dfn[N];
void get_dfn(int u) {
	static int time = 0;
	dfn[u] = ++time;
	for(int v : Tr.sons[u]) get_dfn(v);
}

struct SegmentTree {
	int t[N << 2];
	int max_of(int x, int y) { return a[x] > a[y] ? x : y; }
	void build(int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = x; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		t[x] = max_of(t[x << 1])
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;

	}
};

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); edge[i] = {u, v, 0}; }
	for(int i = 1; i <= Q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x == 1) q[i].u = y, q[i].e = -1;
		else q[i].u = -1, q[i].e = y, edge[y].del = true;
	}
	for(int i = 1; i <= m; i++) if(!edge[i].del) merge(edge[i].u, edge[i].v);
	for(int i = 1; i <= n; i++) if(find(i) != i) Tr.add_son(find(i), i);
	for(int i = Q; i >= 1; i--) if(q[i].e != -1) {
		int u = edge[q[i].e].u, v = edge[q[i].e].v;
		if(find(u) == find(v)) continue;
		Tr.add_son(find(u), find(v));
	}
	get_dfn(1);
	for(int i = 1; i <= Q; i++) {

	}
	return 0;
}