#include <bits/stdc++.h>

typedef long long LL;

const int N = 50000 + 5;

int n, m;
std::vector<int> to[N];

bool vis[N];
int fa[N], dfn[N], sz[N];
bool cycle[N];
int time_stamp;
LL ans = 0;
struct DSU {
	int bl[N], cnt[N];
	void init() { for(int i = 1; i <= n; i++) bl[i] = i, cnt[i] = 1; }
	int find(int x) { return x == bl[x] ? x : bl[x] = find(bl[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? bl[x] = y, cnt[y] += cnt[x], cnt[x] = 0 : 0; }
} cy, ncy;
void dfs(int u) {
	assert(!vis[u]);
	// printf("dfs %d\n", u);
	vis[u] = true, dfn[u] = ++time_stamp;
	int back = 0;
	sz[u] = 1;
	for(int v : to[u]) if(v != fa[u]) {
		if(vis[v]) { if(dfn[v] < dfn[u]) back = v; }
		else fa[v] = u, dfs(v), sz[u] += sz[v];
	}
	if(back) {
		// printf("%d: find cycle on (%d, %d)\n", u, u, back);
		int w = u, tp = u;
		while(w != back) tp = w, w = fa[w];
		w = u;
		while(w != back) cycle[w] = true, cy.cnt[tp]++, cy.bl[w] = tp, w = fa[w];
	}
}

int sum[N];

LL h(int x) { return (LL)x * (x - 1) / 2 - x + 1; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int k, x, last = 0;
		scanf("%d%d", &k, &last);
		while(--k) scanf("%d", &x), to[last].push_back(x), to[x].push_back(last), last = x;
	}
	ncy.init();
	dfs(1);
	for(int i = 2; i <= n; i++) if(!cycle[i]) ncy.merge(i, fa[i]);
	// for(int i = 1; i <= n; i++) printf("%d: fa = %d, cycle = %d, cy.bl = %d, cy.cnt = %d, ncy.find = %d, ncy.cnt = %d\n", i, fa[i], cycle[i], cy.bl[i], cy.cnt[i], ncy.find(i), ncy.cnt[i]);
	LL sumcycle = 0;
	for(int i = 1; i <= n; i++) if(cycle[i] && i == cy.bl[i]) sumcycle += cy.cnt[i] + 1;
	// printf("sumcycle = %lld\n", sumcycle);
	for(int i = 1; i <= n; i++) if(i == ncy.find(i)) ans += h(ncy.cnt[i]) * sumcycle; // , printf("ans += h(ncy.cnt[%d]) * %lld\n", i, sumcycle);
	for(int u = 1; u <= n; u++)
		if(cycle[u]) {
			sum[cy.bl[u]] += ncy.cnt[ncy.find(u)]; // , printf("sum[bl[%d]] += cnt[bl[%d]]\n", u, v);
			ans -= h(ncy.cnt[ncy.find(u)]) * (cy.cnt[cy.bl[u]] + 1); // , printf("ans -= h(ncy.cnt[ncy.find(%d)]) * (cy.cnt[cy.bl[%d]] + 1)\n", u, u);
			if(u == cy.bl[u]) {
				sum[u] += ncy.cnt[ncy.find(fa[u])]; // , printf("sum[%d] += cnt[bl[fa[%d]]]\n", u, u);
				ans -= h(ncy.cnt[ncy.find(fa[u])]) * (cy.cnt[u] + 1); // , printf("ans -= h(ncy.cnt[ncy.find(fa[%d)]) * (cy.cnt[%d] + 1)\n", fa[u], u);
			}
		} else {
			if(u != 1) ans += (LL)sz[u] * (n - sz[u]) - 1; // , printf("%d <-> %d: ans += %d * %d - 1\n", u, fa[u], sz[u], n - sz[u]);
		}
	// for(int u = 1; u <= n; u++) if(cycle[u] && u == cy.bl[u]) printf("sum[%d] = %d\n", u, sum[u]);
	for(int u = 1; u <= n; u++) if(cycle[u] && u == cy.bl[u]) ans += (h(sum[u]) - 1) * (cy.cnt[u] + 1); // , printf("ans += h(sum[%d]) * (cnt[%d] + 1)\n", u, u);
	printf("%lld\n", ans);
	return 0;
}