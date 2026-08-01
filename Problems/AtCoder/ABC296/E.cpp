#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
int a[N];

std::vector<int> b[N];

int f[N], vis[N];
void dfs(int u) {
	if(vis[u] == 2) return;
	else if(vis[u] == 1) { f[u] = n + 1; return; }
	vis[u] = 1;
	for(int v : b[u]) {
		dfs(v);
		f[u] = std::max(f[u], f[v] + 1);
	}
	vis[u] = 2;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) b[a[i]].push_back(i);
	for(int i = 1; i <= n; i++) dfs(i);
	int ans = 0;
	// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
	for(int i = 1; i <= n; i++) ans += (f[i] >= n - 1);
	printf("%d\n", ans);
	return 0;
}