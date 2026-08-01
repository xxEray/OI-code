#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 2; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

struct DSU {
	int fa[N];
	void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu;

int sum[N];
bool vis[N], vise[N << 1];
void dfs(int u, int last) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(i != (last ^ 1)) {
		int v = edge[i].to;
		if(vis[v]) {
			if(!vise[i]) sum[u]++, sum[v]--, vise[i] = vise[i ^ 1] = true;
		} else dfs(v, i);
	}
}

void dfs2(int u, int fa) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs2(v, u);
		sum[u] += sum[v];
	}
	if(sum[u] && fa) dsu.merge(u, fa);
}

std::vector<int> to[N];
int go[21][N], dep[N];
void dfs3(int u) {
	vis[u] = true;
	for(int v : to[u]) if(v != go[0][u]) {
		go[0][v] = u, dep[v] = dep[u] + 1;
		dfs3(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return go[0][u];
}
int sup[N], sdn[N];
bool ans;
void dfs4(int u) {
	vis[u] = true;
	for(int v : to[u]) if(v != go[0][u]) {
		dfs4(v);
		sup[u] += sup[v], sdn[u] += sdn[v];
	}
	if(sup[u] && sdn[u]) ans = false;
}

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
	dsu.init();
	for(int i = 1; i <= n; i++) vis[i] = false;
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs2(1, 0);
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(dsu.find(u) != dsu.find(v)) to[dsu.find(u)].push_back(dsu.find(v));
	}
	// for(int i = 1; i <= n; i++) printf("%d: leader = %d\n", i, dsu.find(i));
	// for(int i = 1; i <= n; i++) if(i == dsu.find(i))
	// 	for(int j : to[i]) printf("->: %d %d\n", i, j);
	for(int i = 1; i <= n; i++) vis[i] = false;
	for(int i = 1; i <= n; i++) if(dsu.find(i) == i && !vis[i]) dfs3(i);
	binary_lifting();
	ans = true;
	for(int i = 1; i <= Q; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u = dsu.find(u), v = dsu.find(v);
		int f = lca(u, v);
		if(f == 0) ans = false;
		sup[u]++, sup[f]--;
		sdn[v]++, sdn[f]--;
	}
	for(int i = 1; i <= n; i++) vis[i] = false;
	for(int i = 1; i <= n; i++) if(dsu.find(i) == i && !vis[i]) dfs4(i);
	puts(ans ? "Yes": "No");
	return 0;
} /*
7 9 3
7 3
3 6
2 4
5 7
6 7
4 5
6 2
5 7
6 1
6 7
4 6
4 5
*/