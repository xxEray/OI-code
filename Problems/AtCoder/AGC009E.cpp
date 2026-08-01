#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e9 + 7;

int n, m, K;

LL f[N * 2][N * 2][2];

int main() {
	scanf("%d%d%d", &n, &m, &K);
	int len = (n + m - 1) / (K - 1);
	f[0][0][0] = 1;
	for(int i = 1; i <= len; i++) for(int j = 0; j <= i * (K - 1); j++)
		for(int k = 0; k < K; k++) if(j - k >= 0) (f[i][j][k != 0] += f[i - 1][j - k][0] + f[i - 1][j - k][1]) %= MOD;
	// for(int i = 1; i <= len; i++) for(int j = 0; j <= i * (K - 1); j++) if(f[i][j][0] || f[i][j][1]) printf("f[%d][%d] = %lld,%lld\n", i, j, f[i][j][0], f[i][j][1]);
	LL ans = 0;
	for(int i = 1; i <= len; i++) for(int j = 0; j <= i * (K - 1); j++) {
		int k = i * (K - 1) - j + 1;
		if(j <= m && j % (K - 1) == m % (K - 1) && k <= n && k % (K - 1) == n % (K - 1)) (ans += f[i][j][1]) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
2 2 2

0.1
0.01
0.11
0.011
0.101
*/