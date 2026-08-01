#include <cstdio>
#include <algorithm>

const int N = 50000 + 5;
const int M = 300 + 5;
const int MOD = 1e9 + 7;

int n, a, b;

int f[2][M][2];

#define l(x) ((x) == 0 ? a : b)

int main() {
	scanf("%d%d%d", &n, &a, &b);
	f[1][1][0] = f[1][1][1] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= std::max(a, b); j++)
			for(int k = 0; k <= 1; k++)
				f[(i & 1) ^ 1][j][k] = 0;
		for(int k = 0; k <= 1; k++)
			for(int j = 1; j <= std::min(i, l(k)); j++) {
				f[(i & 1) ^ 1][j + 1][k] = (f[(i & 1) ^ 1][j + 1][k] + f[i & 1][j][k]) % MOD;
				f[(i & 1) ^ 1][1][!k] = (f[(i & 1) ^ 1][1][!k] + f[i & 1][j][k]) % MOD;
			}
	}
	int ans = 0;
	for(int i = 1; i <= a; i++) ans = (ans + f[n & 1][i][0]) % MOD;
	for(int i = 1; i <= b; i++) ans = (ans + f[n & 1][i][1]) % MOD;
	printf("%d\n", ans);
	return 0;
}