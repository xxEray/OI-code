#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

LL n, m;
LL f[N][N], g[N][N];

int main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 0; i <= m; i++) f[1][i] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = 0; j <= m; j++) {
			for(int k = 0; k < i; k++) (g[i][j] += f[k][j] * f[i - k - 1][j] % MOD) %= MOD;
			for(int k = 0; k <= j / i; k++) (f[i][j] += g[i][j - (i - 1) * (k + i - 2) / (i - 1)])
		}
	return 0;
}