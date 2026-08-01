#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dep[N];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u);
}

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	int mxid = 0;
	for(int i = 1; i <= n; i++) if(dep[i] > dep[mxid]) mxid = i;
	dfs(mxid, 0);
	for(int i = 1; i <= n; i++) if(dep[i] > dep[mxid]) mxid = i;
	int diameter = dep[mxid], cnt = 0;
	for(int i = 1; i <= n; i++) cnt += (dep[i] == dep[mxid]);
	if(cnt > 1) { printf("%d\n", diameter - 1); return 0; }
	dfs(mxid, 0);
	for(int i = 1; i <= n; i++) if(dep[i] > dep[mxid]) mxid = i;
	diameter = dep[mxid], cnt = 0;
	for(int i = 1; i <= n; i++) cnt += (dep[i] == dep[mxid]);
	if(cnt > 1) { printf("%d\n", diameter - 1); return 0; }
	printf("%d\n", diameter - 2);
	return 0;
}