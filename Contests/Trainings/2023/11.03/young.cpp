#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], ek;
	Graph() : ek(1) {}
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
	int fa[N];
	void dfs(int u) {
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dfs(v);
		}
	}
} T1, T2;

int main() {
#ifndef DEBUG
	freopen("young.in", "r", stdin);
	freopen("young.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); T1.add_edge(u, v), T1.add_edge(v, u); }
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); T2.add_edge(u, v), T2.add_edge(v, u); }
	T1.dfs(1), T2.dfs(1);
	// printf("T1.fa: "); for(int i = 1; i <= n; i++) printf("%d ", T1.fa[i]); puts("");
	// printf("T2.fa: "); for(int i = 1; i <= n; i++) printf("%d ", T1.fa[i]); puts("");
	int ans = 0;
	for(int i = 2; i <= n; i++) ans += (T1.fa[i] != T2.fa[i]);
	printf("%d\n", ans);
	return 0;
} /*
5
1 2
2 3
2 4
3 5
1 2
1 3
3 4
1 5
*/