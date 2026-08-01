#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
LL a[N], b[N], c[2 * N];
struct Edge { int u, v; LL w; } edge[N];

struct DSU {
	int fa[2 * N];
	void init(int mx) { for(int i = 1; i <= mx; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu;

int fa[2 * N];
std::vector<int> son[2 * N];
LL sum[2 * N], f[2 * N];
void dfs(int u) {
	for(int v : son[u]) {
		dfs(v);
		sum[u] += sum[v];
	}
	if(u <= n) {
		f[u] = b[u] + c[u];
	} else {
		f[u] = LLINF;
		for(int v : son[u]) f[u] = std::min(f[u], sum[u] - sum[v] + std::max(c[u], f[v]));
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]), c[i] = std::max(a[i] - b[i], 0LL);
	for(int i = 1; i <= m; i++) scanf("%d%d", &edge[i].u, &edge[i].v), edge[i].w = std::max(c[edge[i].u], c[edge[i].v]);
	std::sort(edge + 1, edge + m + 1, [&](Edge x, Edge y) { return x.w < y.w; });
	int cnte = 0;
	dsu.init(n);
	for(int i = 1; i <= m; i++) if(dsu.find(edge[i].u) != dsu.find(edge[i].v)) dsu.merge(edge[i].u, edge[i].v), edge[++cnte] = edge[i];
	assert(cnte == n - 1);
	dsu.init(2 * n);
	for(int i = 1; i < n; i++) {
		int u = dsu.find(edge[i].u), v = dsu.find(edge[i].v);
		dsu.fa[u] = dsu.fa[v] = n + i;
		fa[u] = fa[v] = n + i, son[n + i].push_back(u), son[n + i].push_back(v);
		c[n + i] = edge[i].w;
	}
	for(int i = 1; i <= n; i++) sum[i] = b[i];
	dfs(2 * n - 1);
	printf("%lld\n", f[2 * n - 1]);
	return 0;
}