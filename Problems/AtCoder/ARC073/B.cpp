#include <bits/stdc++.h>

const int N = 100 + 5;

int n, m;
long long w[N], v[N];

long long f[N][N][N * 3];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &w[i], &v[i]);
	long long base = w[1];
	for(int i = 1; i <= n; i++) w[i] -= base;
	memset(f, ~0x3f, sizeof(f));
	f[0][0][0] = 0;
	long long ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; k <= 3 * n; k++) {
				f[i][j][k] = f[i - 1][j][k];
				if(j >= 1 && k >= w[i]) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k - w[i]] + v[i]);
			}
	for(int i = 0; i <= n && i * base <= m; i++)
		for(int j = 0; j <= 3 * n; j++) if(j + i * base <= m)
			ans = std::max(ans, f[n][i][j]);
	printf("%lld\n", ans);
	return 0;
}