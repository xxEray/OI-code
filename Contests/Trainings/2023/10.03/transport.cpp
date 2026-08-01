#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int a[N];
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }

LL avg;
int avgcnt;
LL f[N][N], g[N], sum[N];

int sz[N];
void dfs(int u, int fa) {
	sz[u] = 1, sum[u] = a[u];
	f[u][0] = f[u][1] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to, w = edge[i].w;
		dfs(v, u);
		for(int j = 0; j <= sz[u] + sz[v]; j++) g[j] = LLINF;
		for(int j = 0; j <= sz[u]; j++)
			for(int k = 0; k <= sz[v]; k++)
				g[j + k] = std::min(g[j + k], f[u][j] + f[v][k] + std::abs(sum[v] - (avg * sz[v] + k)) * w);
		for(int j = 0; j <= sz[u] + sz[v]; j++) f[u][j] = g[j];
		sz[u] += sz[v], sum[u] += sum[v];
	}
}

int main() {
// #ifndef DEBUG
// 	freopen("transport.in", "r", stdin);
// 	freopen("transport.out", "w", stdout);
// #endif
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1, avg = avgcnt = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), avg += a[i];
		for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
		avgcnt = avg % n, avg /= n;
		dfs(1, 0);
		// printf("avg = %lld, avgcnt = %d\n", avg, avgcnt);
		// for(int i = 1; i <= n; i++) for(int j = 0; j <= sz[i]; j++) if(f[i][j] < LLINF) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
		printf("%lld\n", f[1][avgcnt]);
	}
	return 0;
} /*
3
3
1 2 3
1 2 1
1 3 1
3
1 3 3
1 2 3
1 3 4
2
1 2
1 2 19
*/