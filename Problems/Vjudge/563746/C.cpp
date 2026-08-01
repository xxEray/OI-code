#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int n, m;
struct Edge { int u, v; } e[M];
std::vector<Edge> ans;
std::vector<std::pair<int, int>> G[N];
std::vector<int> son[N];

int fa[N], dep[N];
bool vis[N], istree[M];
void dfs(int u) {
	vis[u] = true;
	dep[u] = dep[fa[u]] + 1;
	for(auto p : G[u]) if(!vis[p.first]) {
		int v = p.first, id = p.second;
		fa[v] = u;
		dfs(v);
		istree[std::abs(id)] = true;
		if(id < 0) std::swap(e[-id].u, e[-id].v);
		son[u].push_back(v);
	}
}

bool tag[N];
void settag(int u, int v) { tag[u] ^= 1, tag[v] ^= 1; }
int ind[N], oud[N];

std::vector<int> g[2][2];

void dfs2(int u) {
	for(int v : son[u]) {
		dfs2(v);
		tag[u] ^= tag[v];
	}
	if(fa[u]) {
		if(tag[u]) ans.push_back({u, fa[u]});
		else ans.push_back({fa[u], u});
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i] = {u, v};
		G[u].push_back({v, i}), G[v].push_back({u, -i});
	}
	dfs(1);
	for(int i = 1; i <= m; i++) oud[e[i].u] ^= 1, ind[e[i].v] ^= 1;
	for(int i = 1; i <= n; i++) g[ind[i] ^ oud[i]][ind[i]].push_back(i);
	while(g[0][1].size() >= 2) {
		int u = g[0][1].back(), v = g[0][1].end()[-2];
		g[0][1].pop_back(), g[0][1].pop_back();
		settag(u, v);
		ind[u] ^= 1, oud[u] ^= 1, ind[v] ^= 1, oud[v] ^= 1;
		g[0][0].push_back(u), g[0][0].push_back(v);
	}
	if(g[0][1].size() == 1) {
		int u = g[0][1].back();
		g[0][1].pop_back();
		if(g[1][0].empty() && g[1][1].empty()) {
			ans.push_back({u, u});
		} else {
			int v = (g[1][0].empty() ? g[1][1].back() : g[1][0].back());
			g[1][ind[v]].pop_back();
			settag(u, v);
			ind[u] ^= 1, oud[u] ^= 1, ind[v] ^= 1, oud[v] ^= 1;
			g[0][0].push_back(u), g[1][ind[v]].push_back(v);
		}
	}
	while((int)g[1][0].size() - (int)g[1][1].size() >= 4) {
		int u = g[1][0].back(), v = g[1][0].end()[-2];
		g[1][0].pop_back(), g[1][0].pop_back();
		settag(u, v);
		ind[u] ^= 1, oud[u] ^= 1, ind[v] ^= 1, oud[v] ^= 1;
		g[1][1].push_back(u), g[1][1].push_back(v);
	}
	while((int)g[1][1].size() - (int)g[1][0].size() >= 4) {
		int u = g[1][1].back(), v = g[1][1].end()[-2];
		g[1][1].pop_back(), g[1][1].pop_back();
		settag(u, v);
		ind[u] ^= 1, oud[u] ^= 1, ind[v] ^= 1, oud[v] ^= 1;
		g[1][0].push_back(u), g[1][0].push_back(v);
	}
	if((int)g[1][0].size() - (int)g[1][1].size() == 2) g[1][1].push_back(1), g[1][1].push_back(1);
	if((int)g[1][1].size() - (int)g[1][0].size() == 2) g[1][0].push_back(1), g[1][0].push_back(1);
	for(int i = 0; i < (int)g[1][0].size(); i++) ans.push_back({g[1][0][i], g[1][1][i]});
	for(int i = 1; i <= m; i++) if(!istree[i]) ans.push_back({e[i].u, e[i].v});
	dfs2(1);
	printf("%d\n", (int)ans.size());
	for(auto &p : ans) printf("%d %d\n", p.u, p.v);
	return 0;
}