#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 3000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL f[N][N][2];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) f[0][i][0] = 1;
	f[0][0][1] = 1;
	for(int i = 0; i < m; i++) for(int j = 0; j <= n; j++) for(int t = 0; t <= 1; t++) {
		int k = n - j;
		if(j > 0) (f[i + 1][j - 1][t || j - 1 == 0] += f[i][j][t]) %= MOD; // RR
		if(j > 0) (f[i + 1][j][t || j - 1 == 0] += f[i][j][t]) %= MOD; // RB
		if(k > 0) (f[i + 1][j + 1][t] += f[i][j][t]) %= MOD; // BB
		if(k > 0) (f[i + 1][j][t] += f[i][j][t]) %= MOD; // BR
	}
	// for(int i = 0; i <= m; i++) for(int j = 0; j <= n; j++) for(int t = 0; t <= 1; t++) if(f[i][j][t]) printf("f[%d][%d][%d] = %lld\n", i, j, t, f[i][j][t]);
	LL ans = 0;
	for(int i = 0; i <= 2 * m + n; i++) (ans += f[m][i][1]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}