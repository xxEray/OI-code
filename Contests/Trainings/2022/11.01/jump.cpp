#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5000 + 5;
const int MOD = 1e9 + 7;

int n;
char str[N];

LL f[N][N], g[N][N];

int main() {
#ifndef DEBUG
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
#endif
	scanf("%d%s", &n, str + 1);
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		if(str[i] == 'R') {
			for(int j = 0; j <= i; j++) f[i][j] = (f[i - 1][j] * j % MOD + (j ? f[i - 1][j - 1] : 0)) % MOD;
		} else {
			for(int j = 0; j <= i; j++) f[i][j] = (f[i - 1][j] * j % MOD + f[i - 1][j + 1] * j % MOD * (j + 1) % MOD) % MOD;
		}
	/*
		g[i][j] * j -> g[i + 1][j] (str[i + 1]='R')
		g[i][j] -> g[i + 1][j + 1] (str[i + 1]='R')
		g[i][j] * (j + 1) -> g[i + 1][j] (str[i + 1]='L')
		g[i][j] * j^2 -> g[i + 1][j - 1] (str[i + 1]='L')
	*/
	g[n][0] = 1;
	for(int i = n - 1; i >= 1; i--)
		if(str[i + 1] == 'R') {
			for(int j = 0; j <= i; j++) g[i][j] = (g[i + 1][j] * j % MOD + g[i + 1][j + 1]) % MOD;
		} else {
			for(int j = 0; j <= i; j++) g[i][j] = (g[i + 1][j] * (j + 1) % MOD + (j ? g[i + 1][j - 1] * j % MOD * j % MOD : 0)) % MOD;
		}
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) if(f[i][j]) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) if(g[i][j]) printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
	for(int i = 1; i <= n; i++) {
		LL ans = 0;
		if(str[i] == 'R') {
			for(int j = 1; j <= i; j++) (ans += (f[i - 1][j] * j % MOD + f[i - 1][j - 1]) * g[i][j - 1] % MOD) %= MOD;
		} else {
			for(int j = 1; j <= i; j++) (ans += f[i - 1][j] * j % MOD * g[i][j - 1] % MOD + f[i - 1][j] * g[i][j] % MOD) %= MOD;
		}
		printf("%lld ", ans);
	}
	return 0;
}