#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1e5 + 5;

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N], dep[N], go[20][N];
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u, dep[v] = dep[u] + 1;
		dfs(v);
	}
}

void preprocess() {
	for(int i = 1; i <= n; i++) go[0][i] = fa[i];
	for(int j = 1; j < 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i < 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 19; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return fa[u];
}

struct SegmentTreeNode { int v, id; SegmentTreeNode *ls, *rs; } buffer[N * 50];
SegmentTreeNode *nw_node() { static int k = 0; return &buffer[++k]; }
void update(SegmentTreeNode *x) {
	if(!x->ls) x->v = x->rs->v, x->id = x->rs->id;
	else if(!x->rs) x->v = x->ls->v, x->id = x->ls->id;
	else x->v = std::max(x->ls->v, x->rs->v), x->id = (x->v == x->ls->v ? x->ls->id : x->rs->id);
}
struct SegmentTree {
	SegmentTreeNode *rt;
	inline void add(int qind, int qv) { add(qind, qv, rt, 1, 100000); }
	void add(int qind, int qv, SegmentTreeNode *x, int l, int r) {
		assert(x);
		if(l == r) { x->v += qv, x->id = l; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) x->ls ? 0 : x->ls = nw_node(), add(qind, qv, x->ls, l, mid);
		else x->rs ? 0 : x->rs = nw_node(), add(qind, qv, x->rs, mid + 1, r);
		update(x);
	}
	int query_all() { return rt->v ? rt->id : 0; }
} seg[N];
SegmentTreeNode *merge(SegmentTreeNode *x, SegmentTreeNode *y) {
	if(!x || !y) return x ? x : y;
	x->ls = merge(x->ls, y->ls), x->rs = merge(x->rs, y->rs);
	if(!x->ls && !x->rs) x->v += y->v;
	else update(x);
	return x;
}
inline void merge(SegmentTree x, SegmentTree y) { x.rt = merge(x.rt, y.rt); }

int out[N];
void answer(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		answer(v);
		merge(seg[u], seg[v]);
	}
	out[u] = seg[u].query_all();
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) seg[i].rt = nw_node();
	dfs(1), preprocess();
	while(Q--) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		seg[x].add(z, 1), seg[y].add(z, 1);
		int f = lca(x, y);
		seg[f].add(z, -1);
		if(fa[f]) seg[fa[f]].add(z, -1);
	}
	answer(1);
	for(int i = 1; i <= n; i++) printf("%d\n", out[i]);
	return 0;
}