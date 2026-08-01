#include <bits/stdc++.h>

const int N = 8e5 + 5;

int n, K;
int fa[N];
std::vector<int> son[N];

int f[N], sz[N];

void dfs(int u) {
	sz[u] = 1;
	bool flag = false;
	int mx = -1, sum = 0;
	for(int v : son[u]) {
		dfs(v);
		sz[u] += sz[v];
		flag |= (f[v] == 0 && sz[v] >= 2);
		if(sz[v] - 1 >= K) mx = std::max(mx, f[v]);
		sum += f[v];
	}
	f[u] = sum;
	if(sz[u] - 1 >= K) f[u] = std::max(f[u], mx + 1);
	if((int)son[u].size() >= K && flag) f[u] = std::max(f[u], sum + 1);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) f[i] = sz[i] = 0, son[i].clear();
		for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].push_back(i);
		dfs(1);
		// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
		printf("%d\n", f[1]);
	}
	return 0;
} /*
1
20 2
1 1 2 4 3 3 5 5 7 6 9 2 7 3 13 10 5 9 7
*/