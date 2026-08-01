#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const int V = 500 + 5;
const LL MOD = 1e9 + 7;

int n, m;
int a[N];

LL f[N][N][V];

int main() {
#ifndef DEBUG
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1, std::greater<int>());
	f[1][1][a[1]] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = 0; j <= i + 1; j++) for(int k = 0; k <= m + 1; k++) {
			if(!f[i - 1][j][k]) continue;
			if(k + a[i] <= m) (f[i][j + 1][k + a[i]] += f[i - 1][j][k] * (j + 1)) %= MOD;
			(f[i][j][k] += (k - j * (a[i] - 1)) * f[i - 1][j][k]) %= MOD;
			if(j) for(int t = 1; t < a[i] && k + t <= m; t++) (f[i][j][k + t] += f[i - 1][j][k] * 2 * j) %= MOD;
			if(j >= 2) for(int t = 0; t < a[i] && k + t <= m; t++) (f[i][j - 1][k + t] += f[i - 1][j][k] * (j - 1) % MOD * (a[i] - t - 1)) %= MOD;
		}
	LL ans = 0;
	for(int i = 1; i <= n; i++) (ans += f[n][i][m]) %= MOD;
	printf("%lld\n", ans);
	return 0;
} /*
18 477
324 31 27 227 9 21 41 29 50 34 2 362 92 11 13 17 183 119
*/