#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f;

int n, Q;

struct Tree {
	struct Edge { int to, nxt; LL w; } edge[N << 1];
	int head[N];
	void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }
	LL dep[N];
	int fa[N];
	int depth[N];
	void dfs(int u) {
		depth[u] = depth[fa[u]] + 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			dep[v] = dep[u] + edge[i].w;
			fa[v] = u;
			dfs(v);
		}
	}
	int go[21][N];
	void binary_lifting() {
		for(int i = 1; i <= n; i++) go[0][i] = fa[i];
		for(int j = 1; j < 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
	}
	int lca(int u, int v) {
		if(depth[u] < depth[v]) std::swap(u, v);
		for(int i = 0; i < 20; i++) if((depth[u] - depth[v]) >> i & 1) u = go[i][u];
		if(u == v) return u;
		for(int i = 19; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
		return fa[u];
	}
	LL dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
} tr1, tr2;



int main() {
#ifndef DEBUG
	freopen("cqbz.in", "r", stdin);
	freopen("cqbz.out", "w", stdout);
#endif
	int Tid; scanf("%d", &Tid);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); tr1.add_edge(u, v, w), tr1.add_edge(v, u, w); }
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); tr2.add_edge(u, v, w), tr2.add_edge(v, u, w); }
	
	return 0;
}