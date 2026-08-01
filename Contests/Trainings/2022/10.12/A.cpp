#include <cstdio>
#include <algorithm>
#include <cassert>
#include <map>
#include <array>

const int N = 18 + 5;

int n;
int id[4][N][2 * N], a[4][N][2 * N], val[8 * N * N];

struct Edge { int to, nxt; } edge[N * N * 12];
int head[N * N * 4];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
void add_both_edge(int u, int v) { add_edge(u, v), add_edge(v, u); }
int hash(int k, int i, int j) { return k * n * n + id[k][i][j]; }

std::map<std::array<int, 3>, int> f;
int dfs(int u, int l, int r) {
	if(f.count({u, l, r})) return f[{u, l, r}];
	int &ans = f[{u, l, r}];
	int mx1 = 0, mx2 = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(l <= val[v] && val[v] < val[u]) mx1 = std::max(mx1, dfs(v, l, val[u] - 1));
		if(val[u] < val[v] && val[v] <= r) mx2 = std::max(mx2, dfs(v, val[u] + 1, r));
	}
	return ans = mx1 + mx2 + 1;
}

int main() {
#ifndef DEBUG
	freopen("fruit.in", "r", stdin);
	freopen("fruit.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int k = 0; k <= 3; k++) {
		int x = 1, y = n;
		for(int i = 1; i <= n * n; i++) {
			id[k][x][y] = i, scanf("%d", &a[k][x][y]);
			if(y == n + x - 1) x++, y = n - x + 1;
			else y++;
		}
	}
	for(int k = 0; k <= 3; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= 2 * n; j++) if(id[k][i][j]) {
		int t = (((i + j) & 1) == ((1 + n) & 1) ? 1 : -1);
		if(id[k][i + t][j]) add_edge(hash(k, i, j), hash(k, i + t, j));
		if(id[k][i][j - 1]) add_edge(hash(k, i, j), hash(k, i, j - 1));
		if(id[k][i][j + 1]) add_edge(hash(k, i, j), hash(k, i, j + 1));
	}
	for(int k = 0; k <= 2; k++) for(int i = 1; i <= n; i++) add_both_edge(hash(k, i, n + i - 1), hash((k + 1) % 3, i, n - i + 1));
	for(int i = 1; i <= n; i++) add_both_edge(hash(0, n, 2 * (n - i + 1) - 1), hash(3, i, n - i + 1));
	for(int i = 1; i <= n; i++) add_both_edge(hash(1, n, 2 * i - 1), hash(3, i, n + i - 1));
	for(int i = 1; i <= n; i++) add_both_edge(hash(2, n, 2 * (n - i + 1) - 1), hash(3, n, 2 * i - 1));
	int ans = 0;
	for(int k = 0; k <= 3; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= 2 * n; j++)
		if(id[k][i][j]) val[hash(k, i, j)] = a[k][i][j];
	// for(int i = 1; i <= 4 * n * n; i++) printf("val[%d] = %d\n", i, val[i]);
	for(int i = 1; i <= 4 * n * n; i++) ans = std::max(ans, dfs(i, 1, 4 * n * n));
	printf("%d\n", ans);
	return 0;
} /*

*/