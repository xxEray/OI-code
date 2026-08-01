#include <bits/stdc++.h>

const int N = 5000 + 5;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dep[N], fa[21][N];
void dfs(int u) {
	dep[u] = dep[fa[0][u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		fa[0][v] = u;
		dfs(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = fa[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1), binary_lifting();
	long long ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) ans += gcd(gcd(i, j), dist(i, j));
	printf("%lld\n", ans);
	return 0;
}
