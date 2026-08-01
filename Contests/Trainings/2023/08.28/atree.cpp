#include <bits/stdc++.h>

const int N = 4e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int depth[N];
int go[21][N];
void dfs(int u) {
	depth[u] = depth[go[0][u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != go[0][u]) {
		int v = edge[i].to;
		go[0][v] = u;
		dfs(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(depth[u] < depth[v]) std::swap(u, v);
	for(int i = 20; i >= 0; i--) if((depth[u] - depth[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return go[0][u];
}

struct Query { int d, id; };
int out[N];
std::vector<Query> q[N];

bool vis[N];
int size[N];
int allsize, root, rootwt;
void getroot(int u, int fa) {
	int mx = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		size[u] += size[v];
		mx = std::max(mx, size[v]);
	}
	mx = std::max(mx, allsize - size[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { if(r < 1 || r > n) return 0; int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;
void dfs(int u, int fa, int dep, bool type) {
	if(u <= (n + 1) / 2) bit.add(dep, type ? 1 : -1);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, dep + 1, type);
	}
}
void dfs2(int u, int fa, int dep) {
	for(auto &p : q[u]) out[std::abs(p.id)] += (p.id > 0 ? 1 : -1) * bit.query(p.d - dep + 2);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		dfs2(v, u, dep + 1);
	}
}
void calc(int u) {
	dfs(u, 0, 1, true);
	for(auto &p : q[u]) out[std::abs(p.id)] += (p.id > 0 ? 1 : -1) * bit.query(p.d + 1);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, 2, false);
		dfs2(v, u, 2);
		dfs(v, u, 2, true);
	}
	dfs(u, 0, 1, false);
}
void solve(int u) {
	// printf("solve %d\n", u);
	calc(u);
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0);
		rootwt = INF, allsize = size[v], getroot(v, 0), solve(root);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, n + i), add_edge(n + i, u);
		add_edge(v, n + i), add_edge(n + i, v);
		// printf("> %d %d\n> %d %d\n", u, n + i, n + i, v);
	}
	n = 2 * n - 1;
	dfs(1);
	binary_lifting();
	for(int i = 1; i <= m; i++) {
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		d *= 2;
		int f = lca(u, v);
		int ds = (depth[u] + depth[v] - 2 * depth[f]) / 2;
		int x = (depth[u] > depth[v] ? u : v);
		for(int j = 0; j <= 20; j++) if((ds >> j) & 1) x = go[j][x];
		q[u].push_back({d, i}), q[v].push_back({d, i});
		if(ds <= d) q[x].push_back({d - ds, -i}); // , printf("%d: transform to %d %d\n", i, x, d - ds);
	}
	rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
} /*
1 6
6 2
1 7
7 3
2 8
8 4
3 9
9 5

5 3
1 2
1 3
2 4
3 5
4 5 0
4 5 1
4 5 2
*/