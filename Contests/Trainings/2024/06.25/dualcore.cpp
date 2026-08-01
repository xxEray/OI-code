#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
int a[N], fa[N];
std::vector<int> son[N];

LL f[N], sum[N];
void dfs(int u) {
	for(int v : son[u]) {
		dfs(v);
		sum[u] += sum[v];
	}
	LL mx = sum[u] & 1;
	for(int v : son[u]) mx = std::max(mx, f[v] - (sum[u] - sum[v]));
	f[u] = mx + a[u];
	sum[u] += a[u];
	// assert((f[u] & 1) == (sum[u] & 1));
}

int main() {
#ifndef DEBUG
	freopen("dualcore.in", "r", stdin);
	freopen("dualcore.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) sum[i] = f[i] = 0, son[i].clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 2; i <= n; i++) scanf("%d", &fa[i]), son[fa[i]].emplace_back(i);
		dfs(1);
		printf("%lld\n", f[1] + (sum[1] - f[1]) / 2);
	}
	return 0;
}