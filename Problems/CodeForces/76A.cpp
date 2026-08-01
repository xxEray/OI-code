#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 200 + 5;
const int M = 5e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Edge { int u, v; LL g, s; } G[M];
int n, m;
LL cg, cs; // cost G, cost S

int tmp[N], tree[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (fa[x] = y) : 0; }

LL calc() {
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i < n; i++) merge(G[tree[i]].u, G[tree[i]].v);
	for(int i = 1; i <= n; i++) if(find(i) != find(1)) return LLINF;
	LL mxg = 0, mxs = 0;
	for(int i = 1; i < n; i++) mxg = std::max(mxg, G[tree[i]].g), mxs = std::max(mxs, G[tree[i]].s);
	return mxg * cg + mxs * cs;
}

int main() {
	scanf("%d%d%lld%lld", &n, &m, &cg, &cs);
	if(m < n - 1) { puts("-1"); return 0; }
	for(int i = 1; i <= m; i++) { int u, v; LL g, s; scanf("%d%d%lld%lld", &u, &v, &g, &s); G[i] = {u, v, g, s}; }
	std::sort(G + 1, G + m + 1, [](Edge x, Edge y) { return x.g < y.g; });
	LL ans = LLINF;
	for(int i = 1; i < n; i++) tree[i] = i;
	ans = std::min(ans, calc());
	for(int i = n; i <= m; i++) {
		for(int j = 1; j < n; j++) tmp[j] = tree[j];
		tmp[n] = i;
		std::sort(tmp + 1, tmp + n + 1, [](int x, int y) { return G[x].s < G[y].s; });
		for(int j = 1; j <= n; j++) fa[j] = j;
		int cnt = 0;
		for(int j = 1; j <= n && cnt < n - 1; j++) if(find(G[tmp[j]].u) != find(G[tmp[j]].v)) merge(G[tmp[j]].u, G[tmp[j]].v), tree[++cnt] = tmp[j];
		ans = std::min(ans, calc());
	}
	printf("%lld\n", ans >= LLINF ? -1LL : ans);
	return 0;
}