#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;

std::vector<int> from[N];
int to[N];

int vis[N], stk[N], top;
bool cir[N];
void dfs(int u) {
	stk[top++] = u;
	vis[u] = 1;
	if(vis[to[u]] == 2);
	else if(vis[to[u]] == 1) {
		do {
			top--;
			cir[stk[top]] = true;
		} while(stk[top] != to[u]);
	} else dfs(to[u]);
	vis[u] = 2;
}

bool f[N][2], g[N][2];
void dfs2(int u) {
	bool has1 = false, all0 = true;
	for(int v : from[u]) if(!cir[v]) {
		dfs2(v);
		has1 |= f[v][1];
		all0 &= f[v][0];
	}
	if(has1) f[u][0] = true;
	if(all0) f[u][1] = true;
}

int val[N];
void dfs3(int u) {
	for(int v : from[u]) if(!cir[v]) {
		if(val[u] == 0) val[v] = (f[v][1] ? 1 : 0);
		else val[v] = 0;
		dfs3(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &to[i]), from[to[i]].push_back(i);
	for(int i = 1; i <= n; i++) if(!vis[i]) top = 0, dfs(i);
	for(int i = 1; i <= n; i++) if(cir[i]) dfs2(i);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d %d\n", i, f[i][0], f[i][1]);
	for(int i = 1; i <= n; i++) vis[i] = false;
	for(int j = 1; j <= n; j++) if(!vis[j] && cir[j]) {
		std::vector<int> vct;
		vis[j] = true, vct.push_back(j);
		int u = to[j];
		while(u != j) vis[u] = true, vct.push_back(u), u = to[u];
		for(int x : vct) g[x][0] = g[x][1] = false;
		val[vct[0]] = 0, g[vct[0]][0] = true, g[vct[0]][1] = false;
		for(int i = 1; i < (int)vct.size(); i++) g[vct[i]][0] = f[vct[i]][0] || g[vct[i - 1]][1], g[vct[i]][1] = f[vct[i]][1] && g[vct[i - 1]][0];
		if(f[vct[0]][0] || g[vct.back()][1]) {
			val[vct.back()] = (g[vct.back()][1] ? 1 : 0);
			for(int i = (int)vct.size() - 1; i >= 1; i--) val[vct[i - 1]] = (val[vct[i]] == 1 ? 0 : (g[vct[i - 1]][1] ? 1 : 0));
			continue;
		}
		val[vct[0]] = 1, g[vct[0]][1] = true, g[vct[0]][0] = false;
		for(int i = 1; i < (int)vct.size(); i++) g[vct[i]][0] = f[vct[i]][0] || g[vct[i - 1]][1], g[vct[i]][1] = f[vct[i]][1] && g[vct[i - 1]][0];
		if(f[vct[0]][1] && g[vct.back()][0]) {
			val[vct.back()] = 0;
			for(int i = (int)vct.size() - 1; i >= 1; i--) val[vct[i - 1]] = (val[vct[i]] == 1 ? 0 : (g[vct[i - 1]][1] ? 1 : 0));
			continue;
		}
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= n; i++) if(cir[i]) dfs3(i);
	std::vector<int> seq;
	for(int i = 1; i <= n; i++) if(val[i]) seq.push_back(i);
	printf("%d\n", (int)seq.size());
	for(int x : seq) printf("%d ", to[x]);
	puts("");
	return 0;
}