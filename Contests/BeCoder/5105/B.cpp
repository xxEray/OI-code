#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 1e9 + 7;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL fac[N];

LL f[N][N];
LL g[N], h[N];
void dfs(int u, int fa) {
	int sz = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u), sz++;
	for(int j = 0; j <= sz; j++) g[j] = 0;
	g[0] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		for(int j = 0; j <= sz; j++) h[j] = g[j] * f[1][v] % MOD;
		for(int j = 1; j <= sz; j++) (h[j] += g[j - 1] * f[0][v]) %= MOD;
		for(int j = 0; j <= sz; j++) g[j] = h[j];
	}
	// printf("%d: g = ", u); for(int i = 0; i <= sz; i++) printf("%lld ", g[i]); puts("");
	for(int j = 0; j <= sz; j++) (f[0][u] += g[j] * fac[j]) %= MOD;
	for(int j = 0; j <= sz; j++) (f[1][u] += g[j] * fac[j + 1]) %= MOD;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	fac[0] = 1;
	for(int i = 1; i <= n + 1; i++) fac[i] = fac[i - 1] * i % MOD;
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("f[%d]: %lld, %lld\n", i, f[0][i], f[1][i]);
	printf("%lld\n", f[0][1]);
	return 0;
}