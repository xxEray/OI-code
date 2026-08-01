#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 1e9 + 7;

int n;
LL C[N][N];

LL fbuf[N][N][2 * N], *f[N][N];

int main() {
	scanf("%d", &n);
	if(n == 1) { puts("1"); return 0; }
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = fbuf[i][j] + 50;
	f[1][1][0] = f[1][1][1] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = i; j <= n; j++)
			for(int x = -n; x <= n; x++)
				for(int t = 1; t <= j; t++)
					for(int p = 0; p <= t; p++)
						if(std::abs(2 * (x + p) - t) <= t)
							(f[i][j][x] += C[j][t] * C[t][p] % MOD * f[i - 1][j - t][2 * (x + p) - t]) %= MOD;
	LL ans = 0;
	for(int i = 2; i <= n; i++) (ans += f[i][n][0]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}