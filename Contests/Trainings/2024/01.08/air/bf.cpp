#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n;
int w[N];
std::vector<int> to[N];

int dfs(int u, int fa) {
	std::vector<int> vct;
	for(int v : to[u]) if(v != fa) vct.emplace_back(dfs(v, u));
	std::sort(vct.begin(), vct.end(), std::greater<>());
	int mx = 0;
	for(int i = 0; i < (int)vct.size(); i++) mx = std::max(mx, vct[i] + i / w[u] + 1);
	return mx;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].emplace_back(v), to[v].emplace_back(u); }
	for(int i = 1; i <= n; i++) printf("%d\n", dfs(i, 0));
	return 0;
}