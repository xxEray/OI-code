#include <bits/stdc++.h>

#ifndef DEBUG
	#undef assert
	#define assert(...) ((void)0)
#endif

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 998244353;

int n, m, K;
std::vector<int> G[N], DAG[N];

int vis[N], dfn[N], low[N], szscc[N], bl[N], stk[N];
int time_stamp, top, scc = 1;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int v : G[u]) {
		if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			bl[stk[top]] = scc;
			vis[stk[top]] = 2;
			szscc[scc]++;
		} while(stk[top] != u);
	}
}

int ind[N];
int dep[N];
void toposort() {
	for(int i = 1; i <= scc; i++) for(int j : DAG[i]) ind[j]++;
	std::vector<int> vct{1};
	dep[1] = 0;
	while(!vct.empty()) {
		int u = vct.back();
		vct.pop_back();
		for(int v : DAG[u]) if(ind[v]) {
			ind[v]--, dep[v] = std::max(dep[v], dep[u] + 1);
			if(ind[v] == 0) vct.emplace_back(v);
		}
	}
}

std::vector<int> tin[N];
std::vector<std::pair<int, int>> vct[N];

std::vector<int> to[N][N];

LL f[N][N], g[N][N], gu[N][N], gv[N][N];

LL getsum(LL l, LL r) { return l > r ? 0 : (LL)(l + 1 + r + 1) * (r - l + 1) / 2 % MOD; }

int main() {
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	n += 2;
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); G[u + 1].emplace_back(v + 1); }
	if(K == 0) { puts("0"); return 0; }
	for(int i = 2; i <= n - 1; i++) if(!vis[i]) tarjan(i);
	scc++;
	for(int u = 2; u <= n - 1; u++) for(int v : G[u]) if(bl[u] != bl[v]) DAG[bl[u]].emplace_back(bl[v]);
	for(int i = 2; i <= scc - 1; i++) {
		std::sort(DAG[i].begin(), DAG[i].end());
		DAG[i].erase(std::unique(DAG[i].begin(), DAG[i].end()), DAG[i].end());
	}
	for(int i = 2; i <= n - 1; i++) G[1].emplace_back(i), G[i].emplace_back(n);
	G[1].emplace_back(n);
	for(int i = 2; i <= scc - 1; i++) DAG[1].emplace_back(i), DAG[i].emplace_back(scc);
	toposort();
	bl[1] = 1, szscc[1] = 1, bl[n] = scc, szscc[scc] = 1;
	int maxdep = 0;
	for(int i = 1; i <= scc; i++) tin[dep[i]].emplace_back(i), maxdep = std::max(maxdep, dep[i]);
	for(int i = 1; i <= scc; i++) if(tin[i].size() >= 3) { puts("0"); return 0; }
	for(int u = 1; u <= n; u++) for(int v : G[u]) to[u][dep[bl[v]]].emplace_back(v);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) vct[std::max(dep[bl[i]], dep[bl[j]])].emplace_back(i, j); // , printf("(%d, %d)\n", i, j);
	// printf("bl: "); for(int i = 1; i <= n; i++) printf("%d ", bl[i]); puts("");
	// printf("dep: "); for(int i = 1; i <= scc; i++) printf("%d ", dep[i]); puts("");
	// printf("szscc: "); for(int i = 1; i <= scc; i++) printf("%d ", szscc[i]); puts("");
	f[1][1] = 1;
	for(int d = 0; d <= maxdep; d++) {
		for(auto [u, v] : vct[d]) {
			printf("! %d %d %d\n", d, u, v), fflush(stdout);
			if(gu[u][v]) {
				if(szscc[bl[u]] > 1) {
					(f[u][v] += gu[u][v] * (K - 1)) %= MOD;
					for(int nu = to[u][d].back(); nu != u; nu = to[nu][d].back()) (f[nu][v] += gu[u][v] * (K - (to[nu][d].back() != u))) %= MOD;
				} else (f[u][v] += gu[u][v]) %= MOD;
			}
			if(gv[u][v]) {
				if(szscc[bl[v]] > 1) {
					(f[u][v] += gv[u][v] * (K - 1)) %= MOD;
					for(int nv = to[v][d].back(); nv != v; nv = to[nv][d].back()) (f[u][nv] += gv[u][v] * (K - (to[nv][d].back() != v))) %= MOD;
				} else (f[u][v] += gv[u][v]) %= MOD;
			}
			if(g[u][v]) {
				if(u == v) {
					if(szscc[bl[u]] > 1) {
						int nu = u;
						do {
							int nv = v;
							do {
								(f[nu][nv] += getsum(to[nu][d].back() != u && to[nv][d].back() != v, K - 2) * g[u][v]) %= MOD;
								nv = to[nv][d].back();
							} while(nv != v);
							nu = to[nu][d].back();
						} while(nu != u);
					} else (f[u][v] += g[u][v] * (K >= 2 || u == n)) %= MOD;
				} else if(bl[u] != bl[v]) {
					int nu = u;
					do {
						int nv = v;
						do {
							(f[nu][nv] += (LL)(szscc[bl[u]] == 1 ? 1 : K - (to[nu][d].back() != u)) * (szscc[bl[v]] == 1 ? 1 : K - (to[nv][d].back() != v)) % MOD * g[u][v]) %= MOD;
							if(szscc[bl[v]] == 1) break;
							nv = to[nv][d].back();
						} while(nv != v);
						if(szscc[bl[u]] == 1) break;
						nu = to[nu][d].back();
					} while(nu != u);
				} else {
					if(szscc[bl[u]] > 1) {
						for(int nu = u; nu != v; nu = to[nu][d].back()) for(int nv = v; nv != u; nv = to[nv][d].back()) (f[nu][nv] += getsum(to[nu][d].back() != v || to[nv][d].back() != u, K - 1) * g[u][v]) %= MOD;
						for(int nu = u; nu != v; nu = to[nu][d].back()) for(int nv = u; nv != v; nv = to[nv][d].back()) (f[nu][nv] += getsum(to[nu][d].back() != v && to[nv][d].back() != v, K - 2) * g[u][v]) %= MOD;
						for(int nu = v; nu != u; nu = to[nu][d].back()) for(int nv = v; nv != u; nv = to[nv][d].back()) (f[nu][nv] += getsum(to[nu][d].back() != u && to[nv][d].back() != u, K - 2) * g[u][v]) %= MOD;
						for(int nu = v; nu != u; nu = to[nu][d].back()) for(int nv = u; nv != v; nv = to[nv][d].back()) (f[nu][nv] += getsum(0, K - 2) * g[u][v]) %= MOD;
					} else (f[u][v] += g[u][v]) %= MOD;
				}
			}
			// if(d == maxdep) printf("u = %d, v = %d, d = %d (f=%lld, g=%lld, gu=%lld, gv=%lld) (continued)\n", u, v, d, f[u][v], g[u][v], gu[u][v], gv[u][v]);
		}
		if(d == maxdep) continue;
		for(auto [u, v] : vct[d]) {
			printf("? %d %d %d\n", d, u, v), fflush(stdout);
			if(tin[d + 1].size() == 1) {
				for(int nu : to[u][d + 1]) (gu[nu][v] += f[u][v]) %= MOD;
				for(int nv : to[v][d + 1]) (gv[u][nv] += f[u][v]) %= MOD;
				for(int nu : to[u][d + 1]) for(int nv : to[v][d + 1]) (g[nu][nv] += f[u][v]) %= MOD;
			} else {
				assert(tin[d + 1].size() == 2);
				for(int nu : to[u][d + 1]) for(int nv : to[v][d + 1]) if(bl[nu] != bl[nv]) (g[nu][nv] += f[u][v]) %= MOD;
			}
			// printf("u = %d, v = %d, d = %d (f=%lld, g=%lld, gu=%lld, gv=%lld)\n", u, v, d, f[u][v], g[u][v], gu[u][v], gv[u][v]);
		}
	}
	printf("%lld\n", f[n][n]);
	return 0;
} /*
1 0 1
*/