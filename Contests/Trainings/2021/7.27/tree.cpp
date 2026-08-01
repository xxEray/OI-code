#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}; head[u] = k++; }
int n;

int sz[N];
LL ans = 0;

void dfs1(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs1(v, u);
			sz[u] += sz[v];
		}
}

void dfs2(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs2(v, u);
			ans += edge[i].w * std::min(sz[v], sz[1] - sz[v]);
		}
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	dfs1(1, 0), dfs2(1, 0);
	printf("%lld\n", ans * 2);
	return 0;
}
