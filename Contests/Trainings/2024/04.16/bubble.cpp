#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 1e9 + 7;

int n, K, type;

namespace Solve_type1 {
	LL f[2][N][N];
	void main() {
		f[0][0][0] = 1;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= n; j++) for(int k = 0; k <= n; k++) f[i & 1][j][k] = 0;
			for(int k = 0; k <= i; k++) {
				for(int j = i; j <= n; j++) (f[i & 1][j][k] += f[~i & 1][j][k] * (j - i + 1)) %= MOD;
				if(k) {
					LL sum = 0;
					for(int j = i; j <= n; j++) {
						(sum += f[~i & 1][j - 1][k - 1]) %= MOD;
						(f[i & 1][j][k] += sum) %= MOD;
					}
				}
			}
		}
		printf("%lld\n", f[n & 1][n][n - K]);
	}
}

namespace Solve_type2 {
	LL f[N][N], g[N][N];
	LL C[N][N];
	void main() {
		for(int i = 0; i <= n; i++) C[i][0] = 1;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		f[0][0] = 1, f[1][1] = 1;
		for(int j = 0; j <= n - K; j++) g[0][j] = 1;
		for(int j = 1; j <= n - K; j++) g[1][j] = 1;
		for(int i = 2; i <= n; i++) for(int j = 1; j <= n - K; j++) {
			for(int k = 1; k < i; k++) {
				(f[i][j] += C[i - 2][k - 1] * f[i - k][j] % MOD * g[k][j - 1]) %= MOD;
				(f[i][j] += C[i - 2][k - 1] * g[i - k][j - 1] % MOD * f[k][j - 1]) %= MOD;
			}
			g[i][j] = (g[i][j - 1] + f[i][j]) % MOD;
			// printf("[%d][%d]: f=%lld, g=%lld\n", i, j, f[i][j], g[i][j]);
		}
		printf("%lld\n", f[n][n - K]);
	}
}

int main() {
	// freopen("bubble.in", "r", stdin);
	// freopen("bubble.out", "w", stdout);
	scanf("%d%d%d", &n, &K, &type);
	if(type == 1) Solve_type1::main();
	else Solve_type2::main();
	return 0;
}