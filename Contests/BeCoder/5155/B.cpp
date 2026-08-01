#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n, Q;
int a[N], b[N];
struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int fa[N], dfn[N], dep[N], time_stamp;
LL depth[N];
int go[21][N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	dfn[u] = ++time_stamp, go[0][dfn[u]] = u;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		depth[v] = depth[u] + edge[i].w;
		dfs(v);
	}
}
int lower_dep(int u, int v) { return dep[u] < dep[v] ? u : v; }
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = lower_dep(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
	if(u == v) return u;
	int l = dfn[u], r = dfn[v];
	if(l > r) std::swap(l, r);
	int k = 31 ^ __builtin_clz(r - l);
	return fa[lower_dep(go[k][l + 1], go[k][r - (1 << k) + 1])];
}
LL dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

std::pair<int, int> diameter[N];

LL calc(const std::pair<int, int> &p) { return dist(p.first, p.second); }
std::pair<int, int> calc(const std::pair<int, int> &p, int u) {
	auto cmp = [](const std::pair<int, int> &p1, const std::pair<int, int> &p2) { return calc(p1) < calc(p2); };
	return std::max({p, {p.first, u}, {p.second, u}}, cmp);
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= n; i++) if(a[i] <= n) b[a[i]] = i;
	dfs(1);
	binary_lifting();
	int mx = 0;
	for(int i = 0; i <= n; i++) {
		if(!b[i]) { mx = i; break; }
		if(i) diameter[i] = calc(diameter[i - 1], b[i]);
		else diameter[i] = {b[i], b[i]};
		// printf("%d: b = %d, diameter = {%d, %d}\n", i, b[i], diameter[i].first, diameter[i].second);
	}
	while(Q--) {
		int u; LL d;
		scanf("%d%lld", &u, &d);
		int l = 1, r = mx + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(std::max(dist(diameter[mid - 1].first, u), dist(diameter[mid - 1].second, u)) <= d) l = mid + 1;
			else r = mid;
		}
		l--;
		printf("%d\n", l);
	}
	return 0;
} /*
5 4
3 9 0 1 2
1 2 10
3 1 4
3 4 3
3 5 2
3 0
1 0
4 6
4 7
*/