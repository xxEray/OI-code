#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;

int n, d, mod;

LL C[N][N], f[N][N], g[N];

int main() {
	scanf("%d%d%d", &n, &d, &mod);
	if(d == 1) { printf("%d\n", n == 2 ? 4 : 0); return 0; }
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	f[1][0] = 1, g[1] = 1;
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= d; j++)
			for(int p = 1; p <= i - j; p++)
				(f[i][j] += f[i - p][j - 1] * C[i - 2][p - 1] % mod * g[p] % mod) %= mod;
		for(int j = 0; j <= d - 1; j++) (g[i] += f[i][j]) %= mod;
	}
	LL ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= d; j++)
			for(int k = 0; k <= d - j; k++)
				if(k != 1)
					(ans += f[i][j] * f[n - i + 1][k]) %= mod;
	printf("%lld\n", ans * n % mod * (n - 1) % mod * 2 % mod);
	return 0;
}