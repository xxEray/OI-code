#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, Q;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N][21], f[N], fsc[N], g[N], dep[N], climb[N], climbsc[N], go[N][21], gosc[N];
void dfs1(int u) {
	int id = 0, scid = 0;
	dep[u] = dep[fa[u][0]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u][0]) {
		int v = edge[i].to;
		fa[v][0] = u;
		dfs1(v);
		if(f[u] < f[v] + 1) fsc[u] = f[u], f[u] = f[v] + 1, scid = id, id = v;
		else if(fsc[u] < f[v] + 1) fsc[u] = f[v] + 1, scid = v;
	}
	go[u][0] = id;
	gosc[u] = scid;
}
void dfs2(int u) {
	if(g[u] > fsc[u]) climbsc[u] = f[fa[u][0]] == f[u] + 1 ? climbsc[fa[u][0]] : climb[fa[u][0]];
	else climbsc[u] = u;
	if(g[u] > f[u]) climb[u] = f[fa[u][0]] == f[u] + 1 ? climbsc[fa[u][0]] : climb[fa[u][0]];
	else climb[u] = u;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u][0]) {
		int v = edge[i].to;
		if(f[u] == f[v] + 1) g[v] = std::max(g[u], fsc[u]) + 1;
		else g[v] = std::max(g[u], f[u]) + 1;
		dfs2(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs1(1);
	dfs2(1);
	// for(int i = 1; i <= n; i++) printf("%d: f = %d, g = %d, climb = %d, climbsc = %d, go = %d\n", i, f[i], g[i], climb[i], climbsc[i], go[i][0]);
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) go[i][j] = go[go[i][j - 1]][j - 1];
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	scanf("%d", &Q);
	while(Q--) {
		int u, x;
		scanf("%d%d", &u, &x);
		if(std::max(f[u], g[u]) < x) puts("-1");
		else {
			if(x <= dep[u] - dep[climb[u]]) {
				for(int i = 0; i <= 20; i++) if(x >> i & 1) u = fa[u][i];
			} else {
				int dd = dep[u] - dep[climb[u]];
				x -= dd;
				bool flag = (u != climb[u]);
				if(flag) {
					for(int i = 0; i <= 20; i++) if((dd - 1) >> i & 1) u = fa[u][i];
					flag &= u == go[fa[u][0]][0];
					u = fa[u][0];
				}
				if(x) {
					if(flag) x--, u = gosc[u];
					for(int i = 0; i <= 20; i++) if(x >> i & 1) u = go[u][i];
				}
			}
			printf("%d\n", u);
		}
	}
	return 0;
}