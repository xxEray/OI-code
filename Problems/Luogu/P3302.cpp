#include <bits/stdc++.h>

const int N = 8e4 + 5;

int n, m, Q;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int tmp[N], ia[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		int val = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
		ia[val] = a[i];
		a[i] = val;
	}
}

struct SegNode { int sum, ls, rs; };
struct SegmentTree {
	SegNode t[N * 100];
	int tot;
	int copy(int x) { int y = ++tot; t[y] = t[x]; return y; }
	void insert(int &x, int qind, int qv, int l = 1, int r = n) {
		x = copy(x);
		if(l == r) { t[x].sum += qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) insert(t[x].ls, qind, qv, l, mid);
		else insert(t[x].rs, qind, qv, mid + 1, r);
		t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum;
	}
	int query(int xp, int yp, int xn, int yn, int qk, int l = 1, int r = n) const {
		if(l == r) return ia[l];
		int mid = (l + r) >> 1;
		int val = t[t[xp].ls].sum + t[t[yp].ls].sum - t[t[xn].ls].sum - t[t[yn].ls].sum;
		if(val >= qk) return query(t[xp].ls, t[yp].ls, t[xn].ls, t[yn].ls, qk, l, mid);
		else return query(t[xp].rs, t[yp].rs, t[xn].rs, t[yn].rs, qk - val, mid + 1, r);
	}
} seg;

struct DSU {
	int ld[N], sz[N];
	void init() { for(int i = 1; i <= n; i++) ld[i] = i, sz[i] = 1; }
	int find(int x) { return ld[x] == x ? x : ld[x] = find(ld[x]); }
	void merge(int x, int y) {
		x = find(x), y = find(y);
		if(x == y) return;
		if(sz[x] < sz[y]) ld[x] = y, sz[y] += sz[x];
		else ld[y] = x, sz[x] += sz[y];
	}
} dsu;

int ver[N];
int dep[N], go[21][N];
int fa[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	go[0][u] = fa[u];
	ver[u] = ver[fa[u]], seg.insert(ver[u], a[u], 1);
	for(int j = 1; j <= 20; j++) go[j][u] = go[j - 1][go[j - 1][u]];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}

int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int j = 0; j <= 20; j++) if((dep[u] - dep[v]) >> j & 1) u = go[j][u];
	if(u == v) return u;
	for(int j = 20; j >= 0; j--) if(go[j][u] != go[j][v]) u = go[j][u], v = go[j][v];
	return fa[u];
}

int main() {
	scanf("%*d%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dsu.init();
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u), dsu.merge(u, v); }
	discrete();
	// for(int i = 1; i <= n; i++) printf("%d: a=%d, ia=%d\n", i, a[i], ia[i]);
	for(int i = 1; i <= n; i++) if(!fa[i]) dfs(i);
	int lastans = 0;
	while(Q--) {
		char str[3];
		scanf("%s", str);
		if(str[0] == 'Q') {
			int x, y, k;
			scanf("%d%d%d", &x, &y, &k);
			x ^= lastans, y ^= lastans, k ^= lastans;
			int l = lca(x, y), f = fa[l];
			// printf("x = %d, y = %d, l = %d, f = %d\n", x, y, l, f);
			printf("%d\n", lastans = seg.query(ver[x], ver[y], ver[l], ver[f], k));
		} else {
			int x, y;
			scanf("%d%d", &x, &y);
			x ^= lastans, y ^= lastans;
			// printf("x = %d, y = %d\n", x, y);
			if(dsu.sz[dsu.find(x)] > dsu.sz[dsu.find(y)]) std::swap(x, y);
			dsu.merge(x, y);
			add_edge(x, y), add_edge(y, x);
			fa[x] = y;
			dfs(x);
		}
	}
	return 0;
} /*
1
8 4 8
1 1 2 2 3 3 4 4
4 7
1 8
2 4
2 1
Q 8 7 3
Q 3 5 1
Q 10 0 0
L 5 4
L 3 2
L 0 7
Q 9 2 5
Q 6 1 6
*/