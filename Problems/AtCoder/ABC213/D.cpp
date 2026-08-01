#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

std::vector<int> edge[N];
int n;

bool vis[N];
void dfs(int u) {
	printf("%d ", u);
	vis[u] = true;
	for(int v : edge[u]) if(!vis[v]) dfs(v), printf("%d ", u);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); edge[u].push_back(v), edge[v].push_back(u); }
	for(int i = 1; i <= n; i++) std::sort(edge[i].begin(), edge[i].end());
	dfs(1);
	return 0;
}