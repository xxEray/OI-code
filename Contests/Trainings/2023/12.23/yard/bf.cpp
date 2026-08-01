#include <bits/stdc++.h>

const int N = 500 + 5;

int n, d;
int a[N];
std::vector<int> to[N];

int f(int x) {
	int val = 1;
	bool flag = true;
	for(int y = 2; y * y <= x; y++) if(x % y == 0) {
		int cnt = 0;
		while(x % y == 0) cnt++, x /= y, val = -val;
		flag &= (cnt <= d);
	}
	if(x > 1) val = -val;
	// printf("f(%d) = %d\n", x, flag ? val : 0);
	return flag ? val : 0;
}

int g[N];
std::vector<int> vct[N];
void dfs(int u, int fa) {
	vct[u].emplace_back(u);
	for(int v : to[u]) if(v != fa) {
		dfs(v, u);
		vct[u].insert(vct[u].end(), vct[v].begin(), vct[v].end());
		vct[v].clear();
	}
	int sz = vct[u].size();
	for(int i = 0; i < sz; i++) for(int j = i; j < sz; j++) g[u] += f(a[vct[u][i]] * a[vct[u][j]]);
}

int main() {
	scanf("%d%d", &n, &d);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].emplace_back(v), to[v].emplace_back(u); }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("%d\n", g[i]);
	return 0;
}