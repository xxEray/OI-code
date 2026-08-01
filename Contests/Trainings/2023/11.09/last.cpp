#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
struct Edge { int to, nxt; } edge[2 * N << 1];
int head[2 * N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int fa[2 * N];
std::vector<int> son[2 * N];

int ld[2 * N];
int find(int x) { return x == ld[x] ? x : ld[x] = find(ld[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? ld[x] = y : 0; }

LL f[2 * N], g[2 * N], h[2 * N];

void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		son[u].push_back(v);
		dfs(v);
		f[u]++, g[u] += f[v], h[u] += g[v];
	}
}

LL calc(int u) {
	if(u <= n) return g[u] * g[u];
	else return f[u] * (f[u] + 1) * (f[u] - 1) - f[u] * f[u] + 2 * f[u] * h[u];
}

int main() {
#ifndef DEBUG
	freopen("last.in", "r", stdin);
	freopen("last.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, i + n), add_edge(i + n, u), add_edge(v, i + n), add_edge(i + n, v); }
	dfs(n);
	LL ans = 0;
	for(int i = 1; i <= 2 * n; i++) ans += calc(i);
	for(int i = 1; i <= 2 * n; i++) ld[i] = i;
	for(int u = 1; u < n; u++) {
		printf("%lld\n", ans);
		int ff = find(fa[u]);
		LL ec = 0, ef = 0, eg = 0, eh = 0;
		ans -= calc(u);
		for(int v : son[u]) {
			merge(v, ff);
			ans -= calc(v);
			ec++;
			ef += f[v];
			eg += g[v];
			eh += h[v];
		}
		ans -= calc(ff);
		f[ff] += -1 + ef, g[ff] += -ec + eg, h[ff] += -ef + eh;
		ans += calc(ff);
		ff = find(fa[ff]);
		if(ff) {
			ans -= calc(ff);
			g[ff] += -1 + ef, h[ff] += -ec + eg;
			ans += calc(ff);
			ff = find(fa[ff]);
			if(ff) {
				ans -= calc(ff);
				h[ff] += -1 + ef;
				ans += calc(ff);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}