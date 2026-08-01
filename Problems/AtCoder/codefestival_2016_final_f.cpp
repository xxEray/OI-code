#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 300 + 5;
const LL MOD = 1e9 + 7;

int n, m;

LL f[N][N][N];

int main() {
	scanf("%d%d", &n, &m);
	f[0][1][1] = 1;
	for(int i = 0; i < m; i++) for(int j = 0; j <= n; j++) for(int k = 0; k <= j; k++) {
		(f[i + 1][j][k] += f[i][j][k] * (j - k) % MOD) %= MOD;
		(f[i + 1][j][j] += f[i][j][k] * k % MOD) %= MOD;
		(f[i + 1][j + 1][k] += f[i][j][k] * (n - j) % MOD) %= MOD;
	}
	printf("%lld\n", f[m][n][n]);
	return 0;
}