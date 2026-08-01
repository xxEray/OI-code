#include <bits/stdc++.h>

typedef long long LL;

const int N = 400 + 3;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL f[N][N], g[N][N], h[N], h2[N];
int sz[N];
void dfs(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u), sz[u] += sz[edge[i].to];
	for(int q = 1; q <= n; q++) {
		int nsz = 1;
		for(int j = 0; j <= n; j++) h[j] = h2[j] = -LLINF;
		h[1] = a[u] * q;
		for(int e = head[u]; e; e = edge[e].nxt) if(edge[e].to != fa) {
			int v = edge[e].to;
			for(int i = 1; i <= nsz; i++) {
				for(int j = 1; j <= sz[v]; j++)
					h2[i + j] = std::max(h2[i + j], h[i] + f[v][j]);
				h2[i] = std::max(h2[i], h[i] + g[v][q]);
			}
			nsz += sz[v];
			for(int i = 0; i <= sz[u]; i++) h[i] = h2[i], h2[i] = -LLINF;
			nsz = std::min(nsz, q);
		}
		f[u][q] = std::max(f[u][q], h[q]);
		for(int i = 1; i <= q - 1; i++) g[u][q - i] = std::max(g[u][q - i], h[i]);
	}
}

int main() {
#ifndef DEBUG
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) f[i][j] = g[i][j] = -LLINF;
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	LL ans = -LLINF;
	for(int i = 0; i <= n; i++) ans = std::max(ans, f[1][i]);
	printf("%lld\n", ans);
	return 0;
} /*
5
1 2 3 4 5
1 2
1 3
2 4
2 5
*/