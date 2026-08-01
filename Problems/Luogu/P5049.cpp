#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::vector<int> cycle;
int vis[N];
std::vector<int> stk;
void get_cycle(int u, int fa) {
	if(vis[u] == 2) return;
	if(vis[u] == 1) {
		int i = 0;
		while(stk[i] != u) i++;
		for(; i < (int)stk.size(); i++) cycle.push_back(stk[i]);
		return;
	}
	vis[u] = 1;
	stk.push_back(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) get_cycle(edge[i].to, u);
	stk.pop_back();
	vis[u] = 2;
}

bool iscycle[N];
int nxt;
void dfs(int u) {
	vis[u] = true;
	printf("%d ", u);
	if(!iscycle[u]) {
		std::vector<int> vct;
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) vct.emplace_back(edge[i].to);
		std::sort(vct.begin(), vct.end());
		for(int v : vct) dfs(v);
	} else {
		std::vector<int> vct, vct2;
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
			int v = edge[i].to;
			if(!iscycle[v]) vct.emplace_back(v);
			else vct2.emplace_back(v);
		}
		std::sort(vct.begin(), vct.end());
		std::sort(vct2.begin(), vct2.end());
		if(vct2.empty()) {
			for(int v : vct) dfs(v);
		} else if(vct2.size() == 1) {
			for(int v : vct) if(v < vct2.front()) dfs(v);
			if(nxt != n + 1) for(int v : vct) if(v > vct2.front()) { nxt = v; break; }
			if(vct2.front() < nxt) dfs(vct2.front());
			for(int v : vct) if(v > vct2.front()) dfs(v);
		} else {
			for(int v : vct) if(v < vct2.front()) dfs(v);
			for(int v : vct) if(vct2.front() < v && v < vct2.back()) { nxt = v; break; }
			if(nxt == n + 1) nxt = vct2.back();
			dfs(vct2.front());
			nxt = n + 1;
			for(int v : vct) if(vct2.front() < v && v < vct2.back()) dfs(v);
			if(!vis[vct2.back()]) dfs(vct2.back());
			for(int v : vct) if(v > vct2.back()) dfs(v);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	get_cycle(1, 0);
	// printf("cycle: "); for(int x : cycle) printf("%d\n", x); puts("");
	for(int x : cycle) iscycle[x] = true;
	for(int i = 1; i <= n; i++) vis[i] = 0;
	nxt = n + 1;
	dfs(1);
	puts("");
	for(int i = 1; i <= n; i++) assert(vis[i]);
	return 0;
}