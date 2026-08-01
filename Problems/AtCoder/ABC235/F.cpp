#include <cstdio>
#include <algorithm>
#include <assert.h>

typedef long long LL;

const int N = 1e4 + 5;
const int S = (1 << 10) + 5;
const LL MOD = 998244353;

int a[N];
int n, m, mask;

LL f[N][S][2][2], g[N][S][2][2];

int main() {
	char ch = getchar();
	while('0' <= ch && ch <= '9') a[++n] = ch - '0', ch = getchar();
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) { int x; scanf("%d", &x); mask |= 1 << x; }
	// NOTICE  f[][][] maybe count 0
	f[0][0][1][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 1024; j++) {
			(f[i][j][0][0] += f[i - 1][j][0][0]) %= MOD;
			(g[i][j][0][0] += g[i - 1][j][0][0] * 10 % MOD) %= MOD;
			(f[i][j][a[i] == 0][0] += f[i - 1][j][1][0]) %= MOD;
			(g[i][j][a[i] == 0][0] += g[i - 1][j][1][0] * 10 % MOD) %= MOD;
			for(int k = 1; k <= 9; k++) {
				(f[i][j | (1 << k)][0][1] += f[i - 1][j][0][0]) %= MOD;
				(g[i][j | (1 << k)][0][1] += g[i - 1][j][0][0] * 10 % MOD + k * f[i - 1][j][0][0] % MOD) %= MOD;
			}
			for(int k = 1; k <= a[i]; k++) {
				(f[i][j | (1 << k)][k == a[i]][1] += f[i - 1][j][1][0]) %= MOD;
				(g[i][j | (1 << k)][k == a[i]][1] += g[i - 1][j][1][0] * 10 % MOD + k * f[i - 1][j][1][0] % MOD) %= MOD;
			}
			// Now, replace all f[][][][0] to f[][][][1]
			(f[i][j | 1][0][1] += f[i - 1][j][0][1]) %= MOD;
			(g[i][j | 1][0][1] += g[i - 1][j][0][1] * 10 % MOD) %= MOD;
			(f[i][j | 1][a[i] == 0][1] += f[i - 1][j][1][1]) %= MOD;
			(g[i][j | 1][a[i] == 0][1] += g[i - 1][j][1][1] * 10 % MOD) %= MOD;
			for(int k = 1; k <= 9; k++) {
				(f[i][j | (1 << k)][0][1] += f[i - 1][j][0][1]) %= MOD;
				(g[i][j | (1 << k)][0][1] += g[i - 1][j][0][1] * 10 % MOD + k * f[i - 1][j][0][1] % MOD) %= MOD;
			}
			for(int k = 1; k <= a[i]; k++) {
				(f[i][j | (1 << k)][k == a[i]][1] += f[i - 1][j][1][1]) %= MOD;
				(g[i][j | (1 << k)][k == a[i]][1] += g[i - 1][j][1][1] * 10 % MOD + k * f[i - 1][j][1][1] % MOD) %= MOD;
			}
		}
	LL ans = 0;
	for(int j = 0; j < 1024; j++)
		if((j & mask) == mask)
			(ans += g[n][j][0][1] + g[n][j][1][1]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}