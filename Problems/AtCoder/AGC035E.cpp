#include <cstdio>
#include <algorithm>
using std::min;

typedef long long LL;

const int N = 150 + 5;

int n, m;
LL mod;

LL f[N][N], g[N][N][N];

int main() {
	scanf("%d%d%lld", &n, &m, &mod);
	if(!(m & 1)) {
		f[0][0] = 1;
		for(int i = 1; i <= n; i++) {
			// for(int j = 1; j <= i - 2; j++)
			// 	for(int k = 1; k <= min(j, m / 2); k++)
			// 		(f[i][1] += f[j][k]) %= mod;
			for(int j = 0; j <= min(i - 1, m / 2); j++) (f[i][0] += f[i - 1][j]) %= mod;
			for(int j = 1; j <= min(i, m / 2); j++)
				(f[i][j] += f[i - 1][j - 1]) %= mod;
		}
		// for(int i = 1; i <= n / 2; i++)
		// 	for(int j = 0; j <= min(i, m / 2); j++)
		// 		printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
		LL ans1 = 1, ans2 = 1;
		for(int i = 1; i <= n / 2; i++)
			for(int j = 1; j <= min(i, m / 2); j++)
				(ans1 += f[i][j]) %= mod;
		for(int i = 1; i <= n - n / 2; i++)
			for(int j = 1; j <= min(i, m / 2); j++)
				(ans2 += f[i][j]) %= mod;
		// printf("%lld * %lld = ", ans1, ans2);
		printf("%lld\n", ans1 * ans2 % mod);
	} else {
		// TODO
	}
	return 0;
}