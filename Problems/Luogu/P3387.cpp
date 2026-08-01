#include <bits/stdc++.h>

const int N = 1e4 + 5;
const int M = 1e5 + 5;

int n, m;
struct Graph {
	struct Edge { int to, nxt; } edge[M];
	int head[N];
	void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
} G, Tr;

int a[N];

int dfn[N], low[N], vis[N], stk[N];
int bl[N], sum[N];
int time_stamp = 0, top, cnt;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	vis[u] = 1, stk[top++] = u;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) {
		int v = G.edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		cnt++;
		do {
			top--;
			bl[stk[top]] = cnt;
			vis[stk[top]] = 2;
			sum[cnt] += a[stk[top]];
		} while(stk[top] != u);
	}
}

int f[N];
int dfs(int u) {
	if(f[u]) return f[u];
	f[u] = sum[u];
	for(int i = Tr.head[u]; i; i = Tr.edge[i].nxt) {
		int v = Tr.edge[i].to;
		f[u] = std::max(f[u], f[v] + sum[u]);
	}
	return f[u];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); G.add_edge(u, v); }
	for(int i = 1; i <= n; i++) if(vis[i] == 0) tarjan(i);
	for(int i = 1; i <= n; i++) for(int j = G.head[i]; j; j = G.edge[j].nxt) {
		int u = i, v = G.edge[j].to;
		if(bl[u] != bl[v]) Tr.add_edge(bl[u], bl[v]);
	}
	int ans = 0;
	for(int i = 1; i <= cnt; i++) ans = std::max(ans, dfs(i));
	printf("%d\n", ans);
	return 0;
}