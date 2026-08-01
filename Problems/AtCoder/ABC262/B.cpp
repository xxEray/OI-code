#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int a[N][N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); a[u][v] = a[v][u] = 1; }
	int ans = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) for(int k = j + 1; k <= n; k++) ans += a[i][j] && a[j][k] && a[i][k];
	printf("%d\n", ans);
	return 0;
}