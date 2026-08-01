#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int M = 10 + 3;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N][M];

int f[N], g[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
	for(int i = 2; i <= n; i++) f[i] = INF;
	for(int i = 1; i <= n - 1; i++) g[i] = INF;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(a[i][j] && i + j <= n) f[i + j] = std::min(f[i + j], f[i] + 1);
	for(int i = n; i >= 1; i--) for(int j = 1; j <= m; j++) if(a[i][j] && i + j <= n) g[i] = std::min(g[i], g[i + j] + 1);
	// for(int i = 1; i <= n; i++) printf("%d: f = %d, g = %d\n", i, f[i], g[i]);
	for(int i = 2; i <= n - 1; i++) {
		int ans = INF;
		for(int j = std::max(i - m, 1); j <= i - 1; j++) for(int k = 1; k <= m; k++) if(a[j][k] && j + k > i && j + k <= n) ans = std::min(ans, f[j] + g[j + k] + 1);
		printf("%d ", ans == INF ? -1 : ans);
	}
	return 0;
}