#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int MAXK = 200 + 5;
const LL MOD = 998244353;

int n, K;
char s[N];

LL f[N][MAXK], g[N][MAXK];

int main() {
	scanf("%d%d%s", &n, &K, s + 1);
	if(s[1] == '0' || s[1] == '?') g[1][0] = f[1][0] = 1;
	if(s[1] == '1' || s[1] == '?') g[1][K] = f[1][K] = 1;
	for(int i = 1; i <= n; i++) {
		if(s[i] == '0' || s[i] == '?') {
			for(int j = 0; j < K; j++) {
				(g[i][j] += g[i - 1][j + 1]) %= MOD;
				(f[i][j] += f[i - 1][j + 1]) %= MOD;
			}
			(g[i][0] += g[i - 1][0]) %= MOD;
			(f[i][0] += f[i - 1][0] + g[i - 1][0]) %= MOD;
		}
		if(s[i] == '1' || s[i] == '?') {
			for(int j = 1; j <= K; j++) {
				(g[i][j] += g[i - 1][j - 1]) %= MOD;
				(f[i][j] += f[i - 1][j - 1]) %= MOD;
			}
			(g[i][K] += g[i - 1][K]) %= MOD;
			(f[i][K] += f[i - 1][K] + g[i - 1][K]) %= MOD;
		}
		// for(int j = 0; j <= K; j++) printf("[%d][%d]: g=%lld, f=%lld\n", i, j, g[i][j], f[i][j]);
	}
	LL ans = 0;
	for(int j = 0; j <= K; j++) (ans += f[n][j]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
5 1
01?10
*/