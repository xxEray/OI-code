#include <cstdio>
#include <algorithm>

typedef long long LL;

#define int long long

const int N = 1000 + 5;
const int K = 200 + 5;

int n, m, p;

int f[2][K][K], g[2][K][K];

signed main() {
	scanf("%lld%lld%lld", &n, &m, &p);
	for(int i = 1; i <= m; i++) f[1][i][1] = 1;
	for(int j = 1; j <= m; j++)
		for(int k = 0; k <= j; k++)
			g[1][j][k] = ((LL)g[1][j - 1][k] + g[1][j][k - 1] - g[1][j - 1][k - 1] + f[1][j][k] + p) % p;
	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= m; j++) 
			for(int k = 0; k <= j; k++) {
				// f[i + 1][j][k .. j - 1] += f[i][j][k] => f[i][j][k] += f[i - 1][j][0 .. k]
				// f[i + 1][j .. m][k] += f[i][j][k] => f[i][j][k] += f[i - 1][k + 1 .. j][k]
				#define total(x, i, j, r, c) (((LL)g[x][r][c] - g[x][(i) - 1][c] - g[x][r][(j) - 1] + g[x][(i) - 1][(j) - 1] + 2LL * p) % p)
				f[i & 1][j][k] = total((i & 1) ^ 1, j, 0, j, k) + total((i & 1) ^ 1, k + 1, k, j, k);
				g[i & 1][j][k] = ((LL)g[i & 1][j - 1][k] + g[i & 1][j][k - 1] - g[i & 1][j - 1][k - 1] + f[i & 1][j][k] + p) % p;
				// for(int r = 0; r <= k; r++) (f[i][j][k] += f[i - 1][j][r]) %= p;
				// for(int r = k + z1; r <= j; r++) (f[i][j][k] += f[i - 1][r][k]) %= p;
			}
	int ans = 0;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= i; j++)
			(ans += f[n & 1][i][j]) %= p;
	printf("%lld\n", ans + 1);
	return 0;
}