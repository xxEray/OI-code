#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek = 1;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
int a[N];
int n;

int fa[N], cnt[N], ok[N];
void dfs1(int u) {
	cnt[u] += a[u];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs1(v);
		cnt[u] += cnt[v];
	}
}
void dfs2(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		dfs2(v);
		ok[u] |= (ok[v] && cnt[v] >= 2);
	}
}
void dfs3(int u) {
	ok[u] |= ok[fa[u]] && cnt[1] - cnt[u] >= 2;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) dfs3(edge[i].to);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(a[i]) {
		ok[i] = true;
		for(int j = head[i]; j; j = edge[j].nxt)
			ok[edge[j].to] = true;
	}
	dfs1(1);
	// for(int i = 1; i <= n; i++) printf("cnt[%d] = %d\n", i, cnt[i]);
	dfs2(1);
	dfs3(1);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, g[i]);
	for(int i = 1; i <= n; i++) printf("%d ", ok[i]);
	return 0;
} /*
8
0 1 0 1 0 0 1 0
8 6
2 5
7 8
6 5
4 5
6 1
7 3
*/