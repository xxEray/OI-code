#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int chip[N];
int a[N];
bool vis[N];
int order[N];

int fa[N];
int dep[N];
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int deepest[N];
bool check(int x) {
	for(int i = 1; i <= n; i++) vis[i] = false, a[i] = 0, deepest[i] = 0;
	for(int i = 1, j = 1; j <= x; i++, j++) {
		if(i > m) i = 1;
		a[chip[i]]++;
	}
	for(int i = 1; i <= m; i++) vis[chip[i]] = true;
	for(int o = 1; o <= n; o++) {
		int u = order[o];
		deepest[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) deepest[u] = std::max(deepest[u], deepest[edge[i].to] + 1);
		if(!vis[u]) continue;
		if(deepest[u] >= a[u] + 1) { deepest[u] = 0; continue; }
		deepest[u] = 0;
		if(a[u] == 0) continue;
		if(vis[fa[u]] || fa[u] == 0) return false;
		a[fa[u]] = a[u] - 1;
		vis[fa[u]] = true;
	}
	return true;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) chip[i] = false, dep[i] = fa[i] = 0, head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%d", &chip[i]);
		dfs(1);
		for(int i = 1; i <= n; i++) order[i] = i;
		std::sort(order + 1, order + n + 1, [&](int x, int y) { return dep[x] > dep[y]; });
		// for(int i = 1; i <= n; i++) printf("%d ", order[i]);
		int l = 0, r = n;
		while(l < r) {
			int mid = (l + r + 1) >> 1;
			if(check(mid)) l = mid;
			else r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}