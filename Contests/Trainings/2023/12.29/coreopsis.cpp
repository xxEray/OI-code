#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
bool a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int f[3][N];
void dfs(int u, int fa) {
	int now[2][2] = {{0, -INF}, {-INF, -INF}}, nxt[2][2];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		nxt[0][0] = now[0][0] + f[0][v], nxt[0][1] = now[0][1] + f[0][v], nxt[1][0] = now[1][0] + f[0][v], nxt[1][1] = now[1][1] + f[0][v];
		nxt[1][0] = std::max(nxt[1][0], now[0][0] + f[1][v]), nxt[1][1] = std::max(nxt[1][1], now[0][1] + f[1][v]);
		nxt[0][1] = std::max(nxt[0][1], now[0][0] + f[2][v]), nxt[1][1] = std::max(nxt[1][1], now[1][0] + f[2][v]);
		now[0][0] = nxt[0][0], now[0][1] = nxt[0][1], now[1][0] = nxt[1][0], now[1][1] = nxt[1][1];
	}
	if(a[u]) f[0][u] = std::max(now[0][0], now[0][1]), f[1][u] = now[0][0] + 1, f[2][u] = -INF;
	else f[0][u] = std::max({now[0][0], now[1][0], now[1][1]}), f[1][u] = now[1][0] + 1, f[2][u] = std::max(now[0][0], now[0][1]) + 1;
}

int main() {
#ifndef DEBUG
	freopen("coreopsis.in", "r", stdin);
	freopen("coreopsis.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= K; i++) { int x; scanf("%d", &x); a[x] = true; }
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	// for(int i = 1; i <= n; i++) printf("f[%d]: %d %d %d\n", i, f[0][i], f[1][i], f[2][i]);
	printf("%d\n", 2 * (n - K) - f[0][1]);
	return 0;
} /*
6 2
2 6
1 2
2 3
2 4
5 4
5 6
*/