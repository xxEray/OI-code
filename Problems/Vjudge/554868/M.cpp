#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], fa[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], eul[N], eull[2 * N], dep[N], dfnl[N];
int cdfn, ceul;
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	eull[++ceul] = u, eul[u] = ceul;
	dfn[u] = ++cdfn, dfnl[cdfn] = u;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
		eull[++ceul] = u;
	}
}
int lg[2 * N];
int go[21][2 * N];
int calc_dep(int x, int y) { return dep[x] < dep[y] ? x : y; }
void init_lca() {
	dfs(1);
	// printf("dep: "); for(int i = 1; i <= n; i++) printf("%d ", dep[i]); puts("");
	// printf("dfn: "); for(int i = 1; i <= n; i++) printf("%d ", dfn[i]); puts("");
	lg[0] = -1;
	for(int i = 1; i <= ceul; i++) lg[i] = lg[i >> 1] + 1;
	// printf("eull: "); for(int i = 1; i <= ceul; i++) printf("%d ", eull[i]); puts("");
	for(int i = 1; i <= ceul; i++) go[0][i] = eull[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= ceul; i++)
			go[j][i] = calc_dep(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
	if(!u || !v) return 0;
	if(dfn[u] > dfn[v]) std::swap(u, v);
	// printf("lca(%d, %d) = ", u, v);
	u = eul[u], v = eul[v];
	// printf("mindep[%d .. %d] = ", u, v);
	int k = lg[v - u + 1];
	// printf("%d\n", calc_dep(go[k][u], go[k][v - (1 << k) + 1]));
	return calc_dep(go[k][u], go[k][v - (1 << k) + 1]);
}

std::vector<int> add[N], del[N];
int tot;
struct SegNode { int c, v, lv, rv, f, ls, rs; } t[N * 100];
struct SegmentTree {
	int rt;
	void init() { rt = ++tot; }
	void add(int qind, int qv) { add(qind, qv, rt, 1, n); }
	void add(int qind, int qv, int x, int l, int r) {
		if(l == r) {
			t[x].c += qv;
			if(t[x].c) t[x].lv = t[x].rv = t[x].f = dfnl[l], t[x].v = dep[dfnl[l]];
			else t[x].lv = t[x].rv = t[x].f = 0, t[x].v = 0;
			return;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) t[x].ls ? 0 : t[x].ls = ++tot, add(qind, qv, t[x].ls, l, mid);
		else if(qind > mid) t[x].rs ? 0 : t[x].rs = ++tot, add(qind, qv, t[x].rs, mid + 1, r);
		t[x].lv = (t[t[x].ls].lv ? t[t[x].ls].lv : t[t[x].rs].lv);
		t[x].rv = (t[t[x].rs].rv ? t[t[x].rs].rv : t[t[x].ls].rv);
		t[x].v = t[t[x].ls].v + t[t[x].rs].v - dep[lca(t[t[x].ls].rv, t[t[x].rs].lv)];
		t[x].f = (t[t[x].ls].f && t[t[x].rs].f ? lca(t[t[x].ls].f, t[t[x].rs].f) : (t[t[x].ls].f ^ t[t[x].rs].f));
	}
	int query() { return t[rt].v - dep[t[rt].f] + 1; }
} seg[N];

void merge(int &x, int y, int l = 1, int r = n) {
	if(!x || !y) { x = x ^ y; return; }
	if(l == r) {
		t[x].c = t[x].c + t[y].c;
		if(t[x].c) t[x].lv = t[x].rv = t[x].f = dfnl[l], t[x].v = dep[dfnl[l]];
		else t[x].lv = t[x].rv = t[x].f = 0, t[x].v = 0;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[x].ls, t[y].ls, l, mid), merge(t[x].rs, t[y].rs, mid + 1, r);
	t[x].lv = (t[t[x].ls].lv ? t[t[x].ls].lv : t[t[x].rs].lv);
	t[x].rv = (t[t[x].rs].rv ? t[t[x].rs].rv : t[t[x].ls].rv);
	t[x].v = t[t[x].ls].v + t[t[x].rs].v - dep[lca(t[t[x].ls].rv, t[t[x].rs].lv)];
	t[x].f = (t[t[x].ls].f && t[t[x].rs].f ? lca(t[t[x].ls].f, t[t[x].rs].f) : (t[t[x].ls].f ^ t[t[x].rs].f));
}

long long ans;
void solve(int u, int fa) {
	seg[u].init();
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		solve(v, u);
		merge(seg[u].rt, seg[v].rt);
	}
	for(int x : add[u]) /* printf("%d: add %d\n", u, x),  */seg[u].add(dfn[x], 1);
	for(int x : del[u]) /* printf("%d: del %d\n", u, x),  */seg[u].add(dfn[x], -1);
	ans += seg[u].query() - 1;
	// printf("%d: %d\n", u, seg[u].query());
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v); add_edge(v, u); }
	init_lca();
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		int f = lca(u, v);
		add[u].push_back(u), add[u].push_back(v);
		add[v].push_back(u), add[v].push_back(v);
		del[f].push_back(u), del[f].push_back(v);
		del[fa[f]].push_back(u), del[fa[f]].push_back(v);
	}
	solve(1, 0);
	// printf("original ans = %lld\n", ans);
	assert(ans % 2 == 0);
	printf("%lld\n", ans / 2);
	return 0;
} /*
7 2
1 2
1 3
2 4
2 5
5 6
5 7
4 7
5 6
*/