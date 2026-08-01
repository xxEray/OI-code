#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N][N];
int n, m;

LL C;
LL f[N][N], g[N][N];

inline LL min_(LL a, LL b, LL c) { return std::min(a, std::min(b, c)); }

int main() {
	scanf("%d%d%lld", &n, &m, &C);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%lld", &a[i][j]);
	for(int i = 0; i <= n; i++) f[i][0] = g[i][0] = f[i][m + 1] = g[i][m + 1] = LLINF;
	for(int i = 0; i <= m; i++) f[0][i] = g[0][i] = f[n + 1][i] = g[n + 1][i] = LLINF;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++)
			f[i][j] = min_(f[i][j - 1], f[i - 1][j], a[i][j] - C * i - C * j);
		for(int j = m; j >= 1; j--)
			g[i][j] = min_(g[i][j + 1], g[i - 1][j], a[i][j] - C * i + C * j);
		// for(int j = 1; j <= m; j++)
		// 	printf("[%d][%d] = %lld instead of %lld, %lld instead of %lld\n", i, j, f[i][j], a[i][j] - C * i - C * j, g[i][j], a[i][j] - C * i + C * j);
	}
	LL ans = LLINF;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			ans = std::min(ans, a[i][j] + C * i + C * j + std::min(f[i][j - 1], f[i - 1][j]));
			ans = std::min(ans, a[i][j] + C * i - C * j + std::min(g[i][j + 1], g[i - 1][j]));
		}
	printf("%lld\n", ans);
	return 0;
}