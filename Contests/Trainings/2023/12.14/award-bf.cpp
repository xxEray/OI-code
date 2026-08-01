#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, Q;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N];
void predfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		predfs(v);
	}
}

int top[N], dep[N];
void dfs1(int u) {
	top[u] = std::max(a[u], fa[u] == 0 ? 0 : top[fa[u]] + 1);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		dfs1(v);
	}
}
void dfs2(int u) {
	dep[u] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		dfs2(v);
		dep[u] = std::max(dep[u], std::max(a[v], dep[v]) + 1);
	}
}

int main() {
#ifndef DEBUG
	freopen("award.in", "r", stdin);
	freopen("award.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	predfs(1);
	scanf("%d", &Q);
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x] = y;
		dfs1(1), dfs2(1);
		int ans = 0;
		for(int i = 1; i <= n; i++) ans = std::max(ans, a[i]);
		// for(int i = 1; i <= n; i++) printf("%d: top=%d, dep=%d\n", i, top[i], dep[i]);
		for(int u = 1; u <= n; u++) {
			int mx = top[u], sc = 0;
			for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
				int v = edge[i].to;
				int val = std::max(a[v], dep[v]) + 1;
				if(val >= mx) sc = mx, mx = val;
				else if(val >= sc) sc = val;
			}
			ans = std::max(ans, (mx + sc + 1) >> 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}