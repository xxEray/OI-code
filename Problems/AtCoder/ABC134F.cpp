#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 1e9 + 7;

int n, K;
LL f[N][N][N * N];

int main() {
	scanf("%d%d", &n, &K);
	f[1][0][0] = f[1][1][0] = 1;
	for(int i = 1; i < n; i++)
		for(int j = 0; j <= i; j++)
			for(int k = 0; k <= K; k++) {
				(f[i + 1][j][k + 2 * (i - j)] += f[i][j][k]) %= MOD;
				(f[i + 1][j + 1][k + 2 * (i - j)] += f[i][j][k]) %= MOD;
				(f[i + 1][j + 1][k + 2 * (i - j)] += 2 * (i - j) * f[i][j][k]) %= MOD;
				(f[i + 1][j + 2][k + 2 * (i - j)] += (i - j) * (i - j) * f[i][j][k]) %= MOD;
			}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 0; j <= i; j++)
	// 		for(int k = 0; k <= K; k++)
	// 			if(f[i][j][k]) printf("f[%d][%d][%d] = %lld\n", i, j, k, f[i][j][k]);
	printf("%lld\n", f[n][n][K]);
	return 0;
}