#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;

int n;
LL mod;

LL f[N], g[N][N], h[N], sum[N];

LL power2[N];

int main() {
	scanf("%d%lld", &n, &mod);
	power2[0] = 1;
	for(int i = 1; i <= n; i++) power2[i] = power2[i - 1] * 2 % mod;
	for(int i = 1; i <= n; i++) {
		f[i] = power2[std::max(i - 2, 0)];
		for(int j = 1; j <= i; j++) {
			if(i - 2 * j >= 0) (sum[j] += h[i - 2 * j]) %= mod;
			g[i][j] = sum[j] * f[j] % mod;
			if(i == j) (g[i][j] += f[j]) %= mod;
			if(i + j + 1 <= n) (h[i + j + 1] += g[i][j]) %= mod;
			if(i != j) (f[i] += mod - g[i][j]) %= mod;
			// printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
		}
		// printf("f[%d] = %lld\n", i, f[i]);
	}
	printf("%lld\n", f[n]);
	return 0;
} /*
g(i, j) -> g(i + j + 2 * k + 1 .. n, k) [coeficient=f[k]]
*/