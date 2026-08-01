#include <bits/stdc++.h>

const int N = 1000 + 5;
const int M = 2e5 + 5;

int n, m;
int e[M][2];
std::vector<int> to[N];

int vis[N], dfn[N], low[N], bl[N], stk[N], top, time_stamp, scc;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int v : to[u]) {
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}

int f[N], g[N], now;
bool ans[N][N];
void dfs(int u) {
	if(vis[u]) return;
	f[u] = now;
	vis[u] = 1;
	for(int v : to[u]) if(!vis[v]) dfs(v);
}
void solve(int st) {
	for(int i = 1; i <= n; i++) vis[i] = f[i] = 0;
	vis[st] = 1;
	for(int v : to[st]) now = v, dfs(v);
	for(int i = 1; i <= n; i++) g[i] = f[i], f[i] = 0, vis[i] = 0;
	vis[st] = 1;
	std::reverse(to[st].begin(), to[st].end());
	for(int v : to[st]) now = v, dfs(v);
	for(int v : to[st]) ans[st][v] = ((bl[st] == bl[v]) ^ (f[v] == g[v]) ^ 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &e[i][0], &e[i][1]), to[e[i][0]].push_back(e[i][1]);
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	for(int i = 1; i <= n; i++) solve(i);
	for(int i = 1; i <= m; i++) puts(ans[e[i][0]][e[i][1]] ? "diff" : "same");
	return 0;
}