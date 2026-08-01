#include <cstdio>
#include <algorithm>

const int N = 1e3 + 5;

int a[N][N];
int n, m;

int hash(int x, int y) { return (x - 1) * m + y; }

int fa[N * N], size[N * N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? (size[y] += size[x], size[x] = 0, fa[x] = y) : 0; }

inline int bit(int x, int y) { return x >> y & 1; }

int g[N], cnt;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) fa[hash(i, j)] = hash(i, j), size[hash(i, j)] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(j > 1 && !bit(a[i][j], 0) && !bit(a[i][j - 1], 2)) merge(hash(i, j), hash(i, j - 1));
			if(i < n && !bit(a[i][j], 1) && !bit(a[i + 1][j], 3)) merge(hash(i, j), hash(i + 1, j));
			if(j < m && !bit(a[i][j], 2) && !bit(a[i][j + 1], 0)) merge(hash(i, j), hash(i, j + 1));
			if(i > 1 && !bit(a[i][j], 3) && !bit(a[i - 1][j], 1)) merge(hash(i, j), hash(i - 1, j));
		}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(fa[hash(i, j)] == hash(i, j)) g[++cnt] = size[hash(i, j)];
	std::sort(g + 1, g + cnt + 1);
	for(int i = cnt; i >= 1; i--) printf("%d ", g[i]);
	return 0;
}