#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int SQRTN = 450;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
int sq[N + 1000];

int sz[N], rsz[N];
int g[SQRTN][2];
std::vector<int> f[2][N];
void predfs(int u, int fa) {
	rsz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		predfs(v, u);
		rsz[u] += rsz[v];
	}
}
void dfs(int u, int fa) {
	sz[u] = 1;
	f[0][u].resize(sq[rsz[u]] + 1), f[1][u].resize(sq[rsz[u]] + 1);
	f[0][u][1] = f[1][u][1] = 0;
	for(int e = head[u]; e; e = edge[e].nxt) if(edge[e].to != fa) {
		int v = edge[e].to;
		dfs(v, u);
		for(int i = 1; i <= sq[sz[u] + sz[v]]; i++) g[i][0] = g[i][1] = INF;
		for(int i = 1; i <= sq[sz[u]]; i++)
			for(int j = 1; j <= sq[sz[v]]; j++) {
				if(i + j <= sq[sz[u] + sz[v]]) g[i + j][0] = std::min(g[i + j][0], f[0][u][i] + f[0][v][j]), g[i + j][1] = std::min(g[i + j][1], f[1][u][i] + f[1][v][j]);
				g[i][0] = std::min(g[i][0], f[0][u][i] + f[1][v][j] + (int)j * (j - 1) + 2 * j), g[i][1] = std::min(g[i][1], f[1][u][i] + f[0][v][j] + (int)j * (j - 1) / 2 + j);
			}
		for(int i = 1; i <= sq[sz[u] + sz[v]]; i++) f[0][u][i] = g[i][0], f[1][u][i] = g[i][1];
		sz[u] += sz[v];
		std::vector<int>().swap(f[0][v]), std::vector<int>().swap(f[1][v]);
	}
}

int main() {
	for(int i = 1; i * i <= 200704; i++) sq[i * i] = i;
	for(int i = 200704; i >= 1; i--) if(sq[i] == 0) sq[i] = sq[i + 1];
	int T; scanf("%d", &T);
	while(T--) {
		ek = 1;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		predfs(1, 0), dfs(1, 0);
		int ans = INF;
		for(int i = 1; i <= sq[n]; i++) ans = std::min({ans, f[0][1][i] + (int)i * (i - 1) / 2 + i, f[1][1][i] + (int)i * (i - 1) + 2 * i});
		// for(int i = 1; i <= n; i++) for(int j = 1; j <= sq[sz[i]]; j++) printf("f[%d][%d] = %d, %d\n", i, j, f[i][j][0], f[i][j][1]);
		printf("%lld\n", (LL)n * (n - 1) + 2 * n - ans);
		std::vector<int>().swap(f[0][1]), std::vector<int>().swap(f[1][1]);
	}
	return 0;
}