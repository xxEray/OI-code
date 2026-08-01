#include <bits/stdc++.h>

const int N = 1e3 + 5;

int n, m, Q;
int a[N];
std::vector<int> to[N];

int approach[N][N];

int root, near;
void dfs(int u, int fa) {
	approach[root][u] = near;
	for(int v : to[u]) if(v != fa) dfs(v, u);
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 2; i <= n; i++) { int fa; scanf("%d", &fa); to[i].emplace_back(fa), to[fa].emplace_back(i); }
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) approach[i][i] = i;
	for(int u = 1; u <= n; u++) for(int v : to[u]) root = u, near = v, dfs(v, u);
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("approach[%d][%d] = %d\n", i, j, approach[i][j]);
	while(Q--) {
		int u, l, r;
		scanf("%d%d%d", &l, &r, &u);
		for(int i = l; i <= r; i++) u = approach[u][a[i]];
		printf("%d\n", u);
	}
	return 0;
} /*
5 4 3
1 1 3 3
5 2 2 3
3 4 5
1 3 4
1 2 1
*/