#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int fa[N];
std::vector<int> son[N];

int f[N];
void dfs(int u) {
	std::vector<int> vct;
	for(int v : son[u]) dfs(v), vct.emplace_back(f[v]);
	std::sort(vct.begin(), vct.end(), std::greater<>());
	for(int i = 0; i < (int)vct.size(); i++) f[u] = std::max(f[u], vct[i] + i + 1);
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].emplace_back(i);
	dfs(1);
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
	printf("%d\n", f[1]);
	return 0;
}