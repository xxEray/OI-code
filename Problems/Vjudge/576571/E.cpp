#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int sz[N];
LL ans;
std::vector<int> center;
void dfs(int u, int fa) {
	sz[u] = 1;
	int mx = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
		ans += edge[i].w * std::min(sz[v], n - sz[v]);
		mx = std::max(mx, sz[v]);
	}
	if(n - sz[u] <= n / 2 && mx <= n / 2) center.push_back(u);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	dfs(1, 0);
	ans *= 2;
	if(center.size() == 2) {
		int u = center[0], v = center[1];
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to == v) ans -= edge[i].w;
	} else {
		int u = center[0];
		LL mnw = LLINF;
		for(int i = head[u]; i; i = edge[i].nxt) mnw = std::min(mnw, edge[i].w);
		ans -= mnw;
	}
	printf("%lld\n", ans);
	return 0;
}