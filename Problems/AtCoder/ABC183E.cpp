#include <cstdio>
#include <algorithm>

const int N = 2000 + 5;
const int MOD = 1e9 + 7;

char a[N][N];
int n, m;

int dpx[N][N], dpy[N][N], dpz[N][N], dp[N][N];

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%s", a[i] + 1);
	dp[1][1] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(i == 1 && j == 1) continue;
			if(a[i][j] == '#') { dp[i][j] = dpx[i][j] = dpy[i][j] = dpz[i][j] = 0; continue; }
			dpx[i][j] = (dpx[i - 1][j] + dp[i - 1][j]) % MOD;
			dpy[i][j] = (dpy[i][j - 1] + dp[i][j - 1]) % MOD;
			dpz[i][j] = (dpz[i - 1][j - 1] + dp[i - 1][j - 1]) % MOD;
			dp[i][j] = ((long long)dpx[i][j] + dpy[i][j] + dpz[i][j]) % MOD;
		}
	std::printf("%d\n", dp[n][m]);
	return 0;
} /*
3 3
...
.#.
...

*/