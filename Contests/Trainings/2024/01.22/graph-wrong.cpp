#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 998244353;

int n, m, K;
std::vector<int> G[N], DAG[N];

int ind[N];

int vis[N], dfn[N], low[N], szscc[N], bl[N], stk[N];
int time_stamp, top, scc;
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

int dep[N];
void toposort() {
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

std::vector<int> to[N];
std::unordered_map<LL, int> mp;
int cid = 0;
int dfs(int d, int u, int v) {
	LL h = ((LL)d << 30 | u << 15 | v);
	if(mp.count(h)) return mp[h];
	mp[h] = ++cid;
	for(int nu : to[u]) 
}

int main() {
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); G[u].emplace_back(v); }
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	LL base = 1;
	for(int i = 1; i <= scc; i++) if(szscc[i] > 1) (base *= K - 1) %= MOD;
	for(int u = 1; u <= n; u++) for(int v : G[u]) if(bl[u] != bl[v]) DAG[bl[u] + 1].emplace_back(bl[v] + 1);
	n = scc + 1;
	for(int i = 2; i <= n; i++) {
		std::sort(DAG[i].begin(), DAG[i].end());
		DAG[i].erase(std::unique(DAG[i].begin(), DAG[i].end()), DAG[i].end());
		for(int j : DAG[i]) ind[j]++;
	}
	for(int i = 2; i <= n; i++) if(!ind[i]) DAG[1].emplace_back(i), ind[i]++;
	toposort();
	int maxdep = 0;
	for(int i = 1; i <= n; i++) tin[dep[i]].emplace_back(i), maxdep = std::max(maxdep, dep[i]);
	for(int i = 0; i <= n; i++) if(tin[i].size() >= 3) { puts("0"); return 0; }
	
	return 0;
}