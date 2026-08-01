#include <cstdio>
#include <algorithm>
#include <set>

const int N = 4e5 + 5;

int n;
int a[N], p[N];

int f[N], g[N];

int v[N];
void calc(int u) {
	g[u] = std::max(g[u << 1] + g[u << 1 | 1] + v[u], 0);
	f[u] = std::max({f[u << 1], f[u << 1 | 1], g[u]});
}
void dfs(int u) {
	if(u > n) return;
	dfs(u << 1), dfs(u << 1 | 1);
	calc(u);
}
void update(int u) {
	while(u) calc(u), u >>= 1;
}

int ans[N];

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), p[a[i]] = i;
	for(int i = 1; i <= n; i++) v[i] = 1;
	dfs(1);
	for(int i = 1; i <= n; i++) {
		if(i > 1) v[p[i - 1]] = -1, update(p[i - 1]);
		ans[f[1]] = i;
	}
	for(int i = n - 1; i >= 1; i--) ans[i] = std::max(ans[i], ans[i + 1]);
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}