#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

int f[N], a[N];
void dfs(int u, int fa) {
	if(u == 1) f[u] = 0, a[u] = n;
	else f[u] = (a[u] > a[fa] ? f[fa] : f[fa] + 1);
	// printf("dfs %d (a=%d, f=%d, fa=%d)\n", u, a[u], f[u], fa);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		a[v] = edge[i].w;
		dfs(v, u);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i), add_edge(v, u, i); }
		dfs(1, 0);
		int ans = 0;
		for(int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}