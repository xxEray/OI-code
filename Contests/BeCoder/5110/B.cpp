#include <bits/stdc++.h>

typedef long long LL;

const int N = 300 + 5;

int n, K;
LL mod;

LL f[N][N], g[N][N];
LL C[N][N];

int main() {
	scanf("%d%d%lld", &n, &K, &mod);
	for(int i = 0; i <= n + 1; i++) C[i][0] = 1;
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	for(int i = K; i >= 0; i--) {
		f[i][1] = 1;
		for(int j = 1; j <= n + 1; j++) {
			for(int k = 1; k < j; k++) (f[i][j] += f[i][j - k] * g[i + 1][k] % mod * C[j - 2][k - 1]) %= mod;
			g[i][j] = (f[i][j] + g[i + 1][j]) % mod;
			// printf("[%d][%d]: f=%lld, g=%lld\n", i, j, f[i][j], g[i][j]);
		}
	}
	printf("%lld\n", f[0][n + 1]);
	return 0;
}