#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

struct DSU {
	int ld[N];
	int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y : 0; }
} dsu;

bool vis[N];
int c[N], dep[N];
void tarjan(int u, int fa) {
	vis[u] = true;
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(!vis[v]) tarjan(v, u);
		else if(dep[v] < dep[u]) c[u]++, c[v]--;
	}
}
void tarjan2(int u, int fa) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		if(!vis[v]) {
			tarjan2(v, u);
			c[u] += c[v];
		}
	}
	if(c[u]) dsu.merge(u, fa);
}

struct DSU2 {
	int ld[N], sz[N];
	int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (ld[x] = y, sz[y] += sz[x]) : 0; }
} dsu2, dsu3;
bool a[N];

int main() {
#ifndef DEBUG
	freopen("dayu.in", "r", stdin);
	freopen("dayu.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) dsu3.ld[i] = i, dsu3.sz[i] = 1;
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); dsu3.merge(u, v); }
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i, 0);
	for(int i = 1; i <= n; i++) vis[i] = false, dsu.ld[i] = i;
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan2(i, 0);
//	printf("belong: "); for(int i = 1; i <= n; i++) printf("%d ", dsu.find(i)); puts("");
	for(int i = 1; i <= n; i++) if(dsu.find(i) == i) dsu2.ld[i] = i;
	for(int i = 1; i <= n; i++) dsu2.sz[dsu.find(i)]++;
	for(int u = 1; u <= n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(edge[i].w && dsu.find(u) == dsu.find(v)) a[dsu.find(u)] = true;
		}
	for(int u = 1; u <= n; u++)
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(!edge[i].w && dsu.find(u) != dsu.find(v) && !a[dsu.find(u)] && !a[dsu.find(v)]) dsu2.merge(dsu.find(u), dsu.find(v));
		}
//	for(int i = 1; i <= n; i++) if(dsu.find(i) == i) printf("%d: a = %d, sz = %d\n", i, a[i], dsu2.sz[dsu2.find(i)]);
	for(int i = 1; i <= n; i++) {
		int x = dsu.find(i);
		if(a[x]) printf("%d ", dsu3.sz[dsu3.find(i)] - 1);
		else printf("%d ", dsu3.sz[dsu3.find(i)] - dsu2.sz[dsu2.find(x)]);
	}
	return 0;
}
