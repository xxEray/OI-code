#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, K, Q;
int a[N], b[N], pos[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
struct Query { int v, id; };
std::vector<Query> q[N];
std::vector<int> e[N];

int fa[21][N], dep[N];
void predfs(int u) {
	dep[u] = dep[fa[0][u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		fa[0][v] = u;
		predfs(v);
	}
}
int go[21][N], frst[N];
int last[N];
void dfs_go(int u) {
	if(a[u]) go[0][u] = last[a[u] + 1];
	int copy = last[a[u]];
	last[a[u]] = u;
	// printf("go[%d] = %d\n", u, go[0][u]);
	frst[u] = last[1];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		dfs_go(v);
	}
	last[a[u]] = copy;
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) fa[j][i] = fa[j - 1][fa[j - 1][i]];
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = fa[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

int calc_up(int u, int d) {
	// printf("calc_up(%d, %d) = ", u, d);
	d -= dep[u] - dep[frst[u]];
	u = frst[u];
	// fprintf(stderr, "first = %d\n", frst[u]);
	if(d < 0 || !u) return /* puts("0"),  */0;
	assert(a[u] == 1);
	for(int i = 20; i >= 0; i--) if(go[i][u] && dep[u] - dep[go[i][u]] <= d) d -= dep[u] - dep[go[i][u]], u = go[i][u];
	// printf("%d\n", a[u]);
	return a[u];
}

int leader[N];
struct DSU {
	int ld[N], w[N], sz[N];
	void init() { for(int i = 1; i <= Q; i++) ld[i] = i, w[i] = 0, sz[i] = 1; }
	int find(int x) const { assert(1 <= x && x <= Q); return x == ld[x] ? x : find(ld[x]); }
	std::vector<std::array<int, 3>> ops;
	void merge(int x, int y, int wt) {
		assert(1 <= x && x <= Q && 1 <= y && y <= Q);
		x = find(x), y = find(y);
		if(sz[x] > sz[y]) std::swap(x, y);
		if(x == y) { ops.push_back({-1, -1, -1}); return; }
		ops.push_back({x, y, w[y]});
		sz[y] += sz[x], ld[x] = y, w[y] = wt;
	}
	void undo() {
		auto op = ops.back();
		ops.pop_back();
		if(op[0] == -1) return;
		int x = op[0], y = op[1];
		sz[y] -= sz[x], ld[x] = x, w[y] = op[2];
	}
} dsu;

int out[N];

std::vector<std::array<int, 4>> tmp[N];
void dfs_down(int u) {
	// printf("dfs %d\n", u);
	fflush(stdout);
	auto &ops = tmp[u];
	for(auto &p : q[u]) {
		if(leader[p.v]) dsu.merge(p.id, leader[p.v], p.v), ops.push_back({1, -1, p.v, leader[p.v]}), leader[p.v] = dsu.find(leader[p.v]);
		else ops.push_back({2, p.id, p.v, dsu.w[p.id]}), dsu.w[p.id] = p.v, leader[p.v] = p.id;
	}
	if(a[u] && leader[a[u] - 1]) {
		if(leader[a[u]]) {
			dsu.merge(leader[a[u] - 1], leader[a[u]], a[u]), ops.push_back({1, leader[a[u] - 1], a[u], leader[a[u]]});
			leader[a[u] - 1] = 0, leader[a[u]] = dsu.find(leader[a[u]]);
		} else std::swap(leader[a[u] - 1], leader[a[u]]), ops.push_back({3, dsu.w[leader[a[u]]], -1, -1}), dsu.w[leader[a[u]]] = a[u];
	}
	for(auto x : e[u]) out[x] = dsu.w[dsu.find(x)];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		dfs_down(v);
	}
	while(!ops.empty()) {
		auto op = ops.back();
		ops.pop_back();
		if(op[0] == 1) {
			leader[op[2]] = op[3];
			if(op[1] != -1) leader[a[u] - 1] = op[1];
			dsu.undo();
		} else if(op[0] == 2) leader[op[2]] = 0, dsu.w[op[1]] = op[3];
		else if(op[0] == 3) dsu.w[leader[a[u]]] = op[1], std::swap(leader[a[u]], leader[a[u] - 1]);
	}
}

int main() {
	// freopen("/home/eray/Downloads/P7518_6.in", "r", stdin);
	// freopen("/home/eray/Downloads/P7518_6.my", "w", stdout);
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= K; i++) scanf("%d", &b[i]), pos[b[i]] = i;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] = pos[a[i]];
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	predfs(1);
	dfs_go(1);
	binary_lifting();
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		int f = lca(u, v);
		// fprintf(stderr, "lca = %d\n", f);
		int x = calc_up(u, dep[u] - dep[f] - 1);
		// fprintf(stderr, "%d\n", x);
		q[f].push_back({x, i});
		e[v].push_back(i);
	}
	dsu.init();
	for(int i = 1; i <= n; i++) tmp[i].shrink_to_fit();
	dfs_down(1);
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i]);
	return 0;
} /*
7 3 3
2 3 1
2 1 3 3 2 1 3
1 2
2 3
1 4
4 5
4 6
6 7
5
3 5
1 3
7 3
5 7
7 5
*/