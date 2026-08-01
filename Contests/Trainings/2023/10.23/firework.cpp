#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const int M = 50 + 5;
const LL MOD = 998244353;

int n, m;
struct Edge { int to, nxt, id; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int id) { static int k = 1; edge[k] = (Edge){v, head[u], id}, head[u] = k++; }

LL f[N][M], g[N], tmp[M];
void dfs1(int u, int fa) {
	f[u][0] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs1(v, u);
		for(int j = m; j >= 1; j--) (f[u][j] += (f[v][0] + f[v][1]) % MOD * f[u][j - 1] % MOD) %= MOD;
	}
}
void dfs2(int u, int fa) {
	for(int j = 0; j <= m; j++) tmp[j] = f[fa][j];
	for(int j = 1; j <= m; j++) (tmp[j] += MOD - (f[u][0] + f[u][1]) % MOD * tmp[j - 1] % MOD) %= MOD;
	g[u] = (tmp[0] + tmp[1] + tmp[0] * g[fa] % MOD) % MOD;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs2(edge[i].to, u);
}
LL out[N], tmp2[M];
void dfs3(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to, id = edge[i].id;
		dfs3(v, u);
		for(int j = 0; j <= m; j++) tmp[j] = f[u][j];
		for(int j = 1; j <= m; j++) (tmp[j] += MOD - (f[v][0] + f[v][1]) % MOD * tmp[j - 1] % MOD) %= MOD;
		for(int j = m; j >= 1; j--) (tmp[j] += g[u] * tmp[j - 1] % MOD) %= MOD;
		for(int j = 0; j <= m; j++) tmp2[j] = 0;
		for(int j = 0; j <= m; j++) for(int k = 0; k <= m - j; k++) (tmp2[j + k] += f[v][j] * tmp[k]) %= MOD;
		for(int j = 0; j <= m; j++) (out[id] += tmp2[j]) %= MOD;
	}
}

int main() {
#ifndef DEBUG
	freopen("firework.in", "r", stdin);
	freopen("firework.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v, i), add_edge(v, u, i); }
	dfs1(1, 0), dfs2(1, 0), dfs3(1, 0);
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: ", i);
	// 	for(int j = 0; j <= m; j++) printf("%lld ", f[i][j]);
	// 	printf("| %lld\n", g[i]);
	// }
	for(int i = 1; i < n; i++) printf("%lld\n", out[i]);
	return 0;
}