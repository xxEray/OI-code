#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n, m;
std::vector<int> to[N];

bool vis[N];
int val[N];
void dfs(int u) {
	vis[u] = true;
	for(int v : to[u]) if(!vis[v]) {
		val[v] = val[u] + 1;
		dfs(v);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) to[i].clear();
		for(int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			to[u].emplace_back(v), to[v].emplace_back(u);
		}
		for(int i = 1; i <= n; i++) vis[i] = false;
		val[1] = 0, dfs(1);
		for(int i = 1; i <= n; i++) printf("%d ", val[i]);
		puts("");
	}
	return 0;
}