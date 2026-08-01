#include "werewolf.h"
#include <bits/stdc++.h>

const int N = 8e5 + 5;

int n, m, Q;
struct Edge { int u, v; } e[N];

struct DSU {
	int fa[2 * N];
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[std::min(x, y)] = std::max(x, y) : 0; }
} dsu;

int fa1[21][N], fa2[21][N];

std::vector<int> son1[N], son2[N];
int dfn1[N], sz1[N], dfn2[N], sz2[N];
int w1[N], w2[N];

void dfs1(int u, int fa) {
	static int time_stamp = 0;
	dfn1[u] = ++time_stamp;
	sz1[u] = 1;
	for(int v : son1[u]) {
		dfs1(v, u);
		sz1[u] += sz1[v];
	}
}
void dfs2(int u, int fa) {
	static int time_stamp = 0;
	dfn2[u] = ++time_stamp;
	sz2[u] = 1;
	for(int v : son2[u]) {
		dfs2(v, u);
		sz2[u] += sz2[v];
	}
}

int idfn1[N], p[N];

struct Query { int l, r, k, id; } q[N];
int out[N];

struct BIT {
	int t[N];
	void add(int x, int v) { assert(1 <= x && x <= 2 * n - 1); while(x <= 2 * n - 1) t[x] += v, x += x & -x; }
	int query(int r) { assert(0 <= r && r <= 2 * n - 1); int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

std::vector<int> check_validity(int n_, std::vector<int> X, std::vector<int> Y, std::vector<int> S, std::vector<int> E, std::vector<int> L, std::vector<int> R) {
	n = n_; m = X.size(); Q = S.size();
	for(int i = 1; i <= m; i++) e[i].u = X[i - 1], e[i].v = Y[i - 1], e[i].u++, e[i].v++;
	for(int i = 1; i <= n; i++) w1[i] = w2[i] = i;
	std::sort(e + 1, e + m + 1, [&](Edge x, Edge y) { return std::min(x.u, x.v) > std::min(y.u, y.v); });
	for(int i = 1; i <= 2 * n - 1; i++) dsu.fa[i] = i;
	int cnt = n;
	for(int i = 1; i <= m; i++) if(dsu.find(e[i].u) != dsu.find(e[i].v)) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		cnt++;
		fa1[0][u] = fa1[0][v] = cnt, dsu.merge(u, cnt), dsu.merge(v, cnt), w1[cnt] = std::min(w1[u], w1[v]);
	}
	std::sort(e + 1, e + m + 1, [&](Edge x, Edge y) { return std::max(x.u, x.v) < std::max(y.u, y.v); });
	for(int i = 1; i <= 2 * n - 1; i++) dsu.fa[i] = i;
	assert(cnt == 2 * n - 1);
	cnt = n;
	for(int i = 1; i <= m; i++) if(dsu.find(e[i].u) != dsu.find(e[i].v)) {
		int u = dsu.find(e[i].u), v = dsu.find(e[i].v);
		cnt++;
		fa2[0][u] = fa2[0][v] = cnt, dsu.merge(u, cnt), dsu.merge(v, cnt), w2[cnt] = std::max(w2[u], w2[v]);
	}
	assert(cnt == 2 * n - 1);
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= 2 * n - 1; i++)
			fa1[j][i] = fa1[j - 1][fa1[j - 1][i]], fa2[j][i] = fa2[j - 1][fa2[j - 1][i]];
	int rt1, rt2;
	for(int i = 1; i <= 2 * n - 1; i++) {
		if(fa1[0][i]) son1[fa1[0][i]].push_back(i);
		else rt1 = i;
		if(fa2[0][i]) son2[fa2[0][i]].push_back(i);
		else rt2 = i;
	}
	dfs1(rt1, 0), dfs2(rt2, 0);
	for(int i = 1; i <= 2 * n - 1; i++) idfn1[dfn1[i]] = i;
	for(int i = 1; i <= 2 * n - 1; i++) if(i <= n) p[dfn2[i]] = dfn1[i];
	// printf("fa1: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", fa1[0][i]); puts("");
	// printf("fa2: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", fa2[0][i]); puts("");
	// printf("w1: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", w1[i]); puts("");
	// printf("w2: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", w2[i]); puts("");
	// printf("dfn1: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", dfn1[i]); puts("");
	// printf("dfn2: "); for(int i = 1; i <= 2 * n - 1; i++) printf("%d ", dfn2[i]); puts("");
	int cn = 0;
	for(int i = 1; i <= Q; i++) {
		int s, t, l, r;
		s = S[i - 1], t = E[i - 1], l = L[i - 1], r = R[i - 1];
		s++, t++, l++, r++;
		for(int j = 20; j >= 0; j--) if(fa1[j][s] && w1[fa1[j][s]] >= l) s = fa1[j][s];
		for(int j = 20; j >= 0; j--) if(fa2[j][t] && w2[fa2[j][t]] <= r) t = fa2[j][t];
		// printf("s = %d, t = %d, [%d, %d] [%d, %d]\n", s, t, dfn1[s], dfn1[s] + sz1[s] - 1, dfn2[t], dfn2[t] + sz2[t] - 1);
		cn++, q[cn].l = dfn1[s], q[cn].r = dfn1[s] + sz1[s] - 1, q[cn].k = dfn2[t] + sz2[t] - 1, q[cn].id = i;
		cn++, q[cn].l = dfn1[s], q[cn].r = dfn1[s] + sz1[s] - 1, q[cn].k = dfn2[t] - 1, q[cn].id = -i;
	}
	std::sort(q + 1, q + cn + 1, [&](Query x, Query y) { return x.k < y.k; });
	for(int i = 0, j = 1; i <= 2 * n - 1; i++) {
		if(i && p[i]) bit.add(p[i], 1);
		while(j <= cn && q[j].k == i) out[std::abs(q[j].id)] += (q[j].id > 0 ? 1 : -1) * bit.query(q[j].l, q[j].r), j++;
	}
	std::vector<int> ans;
	for(int i = 1; i <= Q; i++) ans.push_back(out[i] ? 1 : 0);
	return ans;
}