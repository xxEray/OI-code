#include <bits/stdc++.h>

typedef long long LL;

const int N = 1.5e4 + 5;

int n, m;
std::vector<int> to[N];

namespace Solve_Tree {
	int fa[N], sz[N];
	LL f[N], g[N];
	void predfs(int u) {
		sz[u] = 1;
		for(int v : to[u]) if(v != fa[u]) {
			fa[v] = u;
			predfs(v);
			sz[u] += sz[v];
		}
	}
	void dfs1(int u) {
		f[u] = sz[u];
		for(int v : to[u]) if(v != fa[u]) {
			dfs1(v);
			f[u] += f[v];
		}
	}
	void dfs2(int u) {
		if(fa[u]) g[u] = (n - sz[u]) + f[fa[u]] - sz[fa[u]] - f[u] + g[fa[u]];
		for(int v : to[u]) if(v != fa[u]) dfs2(v);
	}
	void main() {
		predfs(1);
		dfs1(1), dfs2(1);
		LL ans = 0;
		for(int u = 1; u <= n; u++) {
			LL sum = n + g[u];
			for(int v : to[u]) if(v != fa[u]) sum += f[v];
			ans = std::max(ans, sum);
		}
		printf("%lld\n", ans);
	}
}

namespace Solve_TreeWithCycle {
	bool cycle[N];
	std::vector<int> vct;
	int cnt;
	int vis[N], time_stamp;
	int stk[N], top;
	void get_cycle(int u, int ff) {
		vis[u] = ++time_stamp;
		stk[top++] = u;
		for(int v : to[u]) if(v != ff) {
			if(vis[v]) {
				if(vis[v] < vis[u]) {
					do {
						top--;
						vct.emplace_back(stk[top]);
						for(int x : vct) cycle[x] = true;
						cnt = vct.size();
					} while(stk[top] != v);
				}
			} else get_cycle(v, u);
		}
		if(top) top--;
	}
	int fa[N], sz[N];
	LL f[N], g[N];
	void predfs(int u) {
		sz[u] = 1;
		for(int v : to[u]) if(v != fa[u] && !cycle[v]) {
			fa[v] = u;
			predfs(v);
			sz[u] += sz[v];
		}
	}
	void dfs1(int u) {
		f[u] = sz[u];
		for(int v : to[u]) if(v != fa[u] && !cycle[v]) {
			dfs1(v);
			f[u] += f[v];
		}
	}
	void dfs2(int u) {
		if(fa[u]) g[u] = (n - sz[u]) + f[fa[u]] - sz[fa[u]] - f[u] + g[fa[u]];
		for(int v : to[u]) if(v != fa[u] && !cycle[v]) dfs2(v);
	}
	LL s[2 * N];
	LL sum(int len, int l) {
		int r = l + len - 1;
		return s[r] - (l ? s[l - 1] : 0);
	}
	LL h[N], ht[N];
	void main() {
		get_cycle(1, 0);
		for(int u : vct) predfs(u);
		for(int u : vct) dfs1(u);
		for(int i = 0; i < 2 * cnt; i++) s[i] = (i ? s[i - 1] : 0) + sz[vct[i % cnt]];
		for(int i = 1; i < cnt; i++) {
			for(int j = 0; j < cnt; j++) ht[j] = sum(i, j) + std::max(h[j], h[j + 1 == cnt ? 0 : j + 1]);
			// if(i == cnt - 1) for(int j = 0; j < cnt; j++) printf("h[%d][%d] = %lld\n", i, vct[j], ht[j]);
			memcpy(h, ht, sizeof(LL) * cnt);
		}
		LL sumf = 0;
		for(int u : vct) sumf += f[u] - sz[u];
		for(int j = 0; j < cnt; j++) g[vct[j]] = ht[(j + 1) % cnt] + sumf - (f[vct[j]] - sz[vct[j]]);
		// for(int j = 0; j < cnt; j++) printf("g[%d] = %lld (sz=%d)\n", vct[j], g[vct[j]], sz[vct[j]]);
		for(int u : vct) dfs2(u);
		// for(int i = 1; i <= n; i++) printf("f[%d] = %lld, g[%d] = %lld\n", i, f[i], i, g[i]);
		LL ans = 0;
		for(int u = 1; u <= n; u++) {
			LL sum = n + g[u];
			for(int v : to[u]) if(v != fa[u] && !cycle[v]) sum += f[v];
			ans = std::max(ans, sum);
		}
		printf("%lld\n", ans);
	}
}

int main() {
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].emplace_back(v), to[v].emplace_back(u); }
	if(m == n - 1) Solve_Tree::main();
	else Solve_TreeWithCycle::main();
	return 0;
} /*
10 10
1 2
1 4
1 5
1 10
2 3
3 4
3 8
5 6
5 7
8 9
*/