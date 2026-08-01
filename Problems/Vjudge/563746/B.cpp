#include <bits/stdc++.h>

typedef long long LL;

const int N = 1000 + 5;
const int M = 2000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL X;
struct Edge { int u, v; LL w; } edge[M];

std::vector<std::pair<int, LL>> to[N];

struct DSU {
	int fa[M];
	bool tag;
	void init(int mx) { for(int i = 1; i <= mx; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsu0, dsu1, dsu2;

bool chosen[M];

int go[21][N], dep[N];
LL gomx[21][N];
void dfs(int u) {
	dep[u] = dep[go[0][u]] + 1;
	for(auto &p : to[u]) {
		int v = p.first; LL w = p.second;
		if(v == go[0][u]) continue;
		go[0][v] = u;
		gomx[0][v] = w;
		dfs(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++) {
			go[j][i] = go[j - 1][go[j - 1][i]];
			gomx[j][i] = std::max(gomx[j - 1][i], gomx[j - 1][go[j - 1][i]]);
		}
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return go[0][u];
}
LL max_of(int u, int d) {
	LL ret = 0;
	for(int i = 0; i <= 20; i++) if(d >> i & 1) ret = std::max(ret, gomx[i][u]), u = go[i][u];
	return ret;
}

int main() {
	scanf("%d%d%lld", &n, &m, &X);
	for(int i = 1; i <= m; i++) scanf("%d%d%lld", &edge[i].u, &edge[i].v, &edge[i].w);
	std::sort(edge + 1, edge + m + 1, [&](Edge x, Edge y) { return x.w < y.w; });
	// for(int i = 1; i <= m; i++) printf("%d %d %lld\n", edge[i].u, edge[i].v, edge[i].w);
	dsu0.init(m), dsu1.init(m);
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) to[j].clear();
		for(int j = 1; j <= m; j++) chosen[j] = false;
		LL w = 0;
		dsu2.init(n);
		dsu2.merge(edge[i].u, edge[i].v);
		to[edge[i].u].emplace_back(edge[i].v, edge[i].w);
		to[edge[i].v].emplace_back(edge[i].u, edge[i].w);
		w += edge[i].w, chosen[i] = true;
		for(int j = 1; j <= m; j++) if(j != i && dsu2.find(edge[j].u) != dsu2.find(edge[j].v)) {
			dsu2.merge(edge[j].u, edge[j].v);
			to[edge[j].u].emplace_back(edge[j].v, edge[j].w);
			to[edge[j].v].emplace_back(edge[j].u, edge[j].w);
			w += edge[j].w, chosen[j] = true;
		}
		for(int j = 1; j <= n; j++) dep[j] = 0;
		for(int j = 1; j <= n; j++) for(int k = 0; k <= 20; k++) go[k][j] = 0, gomx[k][j] = 0;
		dfs(1);
		gomx[0][dep[edge[i].u] > dep[edge[i].v] ? edge[i].u : edge[i].v] = 0;
		binary_lifting();
		// printf("mst %d: delete %d\n", i, dep[edge[i].u] > dep[edge[i].v] ? edge[i].u : edge[i].v);
		for(int j = 1; j <= m; j++)
			if(!chosen[j]) {
				int u = edge[j].u, v = edge[j].v, f = lca(u, v);
				LL replace = std::max(max_of(u, dep[u] - dep[f]), max_of(v, dep[v] - dep[f]));
				if(!replace) continue;
				// if(i == 9 || j == 9) printf("mst %d: replacing %d, weight = %lld\n", i, j, w - replace + edge[j].w);
				if(w - replace + edge[j].w < X) dsu0.merge(i, j);
				if(w - replace + edge[j].w <= X) dsu1.merge(i, j);
			} else {
				// if(i == 9 || j == 9) printf("mst %d: %d is inside, weight = %lld\n", i, j, w);
				if(w < X) dsu0.merge(i, j);
				if(w <= X) dsu1.merge(i, j);
			}
	}
	// printf("dsu0: "); for(int i = 1; i <= m; i++) printf("%d ", dsu0.find(i)); puts("");
	// printf("dsu1: "); for(int i = 1; i <= m; i++) printf("%d ", dsu1.find(i)); puts("");
	int cnt0 = 0, cnt1 = 0;
	for(int i = 1; i <= m; i++) cnt0 += (dsu0.find(i) == i), cnt1 += (dsu1.find(i) == i);
	// printf("cnt = %d, %d\n", cnt0, cnt1);
	LL ans0 = 1, ans1 = 1;
	while(cnt0--) (ans0 *= 2) %= MOD;
	while(cnt1--) (ans1 *= 2) %= MOD;
	printf("%lld\n", (ans0 - ans1 + MOD) % MOD);
	return 0;
} /*
8 10
49
3 4 1
5 2 2
4 2 4
5 8 9
4 6 10
1 8 10
7 8 10
8 4 11
3 1 13
3 8 128773450
*/