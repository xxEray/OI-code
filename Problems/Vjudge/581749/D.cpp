#include <bits/stdc++.h>

const int N = 5000 + 5;

int n, m;
int e[N][3];
std::multiset<int> to[N];

bool vis[N];
void dfs(int u) {
	for(int v : to[u]) if(!vis[v]) vis[v] = true, dfs(v);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
	for(int i = 1; i <= m; i++) {
		to[e[i][0]].insert(e[i][1]);
		if(!e[i][2]) to[e[i][1]].insert(e[i][0]);
	}
	for(int i = 1; i <= m; i++) {
		if(e[i][2]) { puts("0"); continue; }
		for(int j = 1; j <= n; j++) vis[j] = false;
		to[e[i][0]].erase(to[e[i][0]].find(e[i][1]));
		dfs(e[i][0]);
		if(vis[e[i][1]]) puts("1");
		else {
			to[e[i][0]].insert(e[i][1]), to[e[i][1]].erase(to[e[i][1]].find(e[i][0]));
			puts("0");
		}
	}
	return 0;
}