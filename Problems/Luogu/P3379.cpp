#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n, m, rt;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dep[N], go[N][21];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	go[u][0] = fa;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
	}
}

void preprocess() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[i][j] = go[go[i][j - 1]][j - 1];
}

int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	int d = dep[u] - dep[v];
	for(int i = 0; i <= 20; i++) if(d >> i & 1) u = go[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[u][i] != go[v][i]) u = go[u][i], v = go[v][i];
	return go[u][0];
}

int main() {
	scanf("%d%d%d", &n, &m, &rt);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(rt, 0);
	preprocess();
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", lca(u, v));
	}
	return 0;
}