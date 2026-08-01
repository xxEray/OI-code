#include <bits/stdc++.h>

const int N = (1 << 21) + 5;

int n, m, st;

int id[10][10];
std::pair<int, int> val[100];

int f[N];
int dfs(int u) {
	if(f[u] != -1) return f[u];
	int fa[n + 2], copy[n + 2];
	std::function<int(int)> find = [&](int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); };
	auto merge = [&](int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; };
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 0; i < n * (n - 1) / 2; i++) if(u >> i & 1) merge(val[i].first, val[i].second);
	for(int i = 1; i <= n; i++) copy[i] = fa[i];
	f[u] = 0;
	for(int j = 0; j < n * (n - 1) / 2; j++) if(~u >> j & 1) {
		for(int i = 1; i <= n; i++) fa[i] = copy[i];
		merge(val[j].first, val[j].second);
		if(find(1) != find(n)) f[u] |= !dfs(u | (1 << j));
	}
//	printf("dfs %d ", u); for(int i = 0; i < n * (n - 1) / 2; i++) if(u >> i & 1) printf("(%d,%d) ", val[i].first, val[i].second); printf("= %d\n", f[u]);
	return f[u];
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		int c = 0;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) id[i][j] = id[j][i] = c, val[c] = {i, j}, c++;
		st = 0;
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); st |= 1 << id[u][v]; }
		int U = (1 << (n * (n - 1) / 2));
		for(int s = 0; s <= U; s++) f[s] = -1;
		puts(dfs(st) ? "Cypher" : "Deadlock");
	}
	return 0;
} /*
2
3 0
6 2
1 2
2 3
*/
