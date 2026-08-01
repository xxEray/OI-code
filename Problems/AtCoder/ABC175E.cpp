#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3000 + 5;
const int K = 2e5 + 5;

LL a[N][N];
int n, m, k;

LL f[N][N][4];

int main() {
	std::scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int x, y;
		LL t;
		std::scanf("%d%d%lld", &x, &y, &t);
		a[x][y] = std::max(0LL, t);
	}
	f[1][1][(bool)a[1][1]] = a[1][1];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= 3; k++) {
				if(j > 1) {
					if(k && a[i][j])
						f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k - 1] + a[i][j]);
					f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k]);
				}
				if(i > 1 && k == (bool)a[i][j]) {
					for(int t = 0; t <= 3; t++)
						f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][t] + a[i][j]);
				}
			}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= m; j++) {
	// 		int ret = 0, ind = 0;
	// 		for(int k = 0; k <= 3; k++)
	// 			if(ret < f[i][j][k])
	// 				ret = f[i][j][k], ind = k;
	// 		std::printf("%d(%d) %c", ret, ind, j == m ? '\n' : ' ');
	// 	}
	LL ans = 0;
	for(int k = 0; k <= 3; k++) ans = std::max(ans, f[n][m][k]);
	std::printf("%lld\n", ans);
	return 0;
} /*
4 5 10
2 5 12
1 5 12
2 3 15
1 2 20
1 1 28
2 4 26
3 2 27
4 5 21
3 5 10
1 3 10

28 20 10 0  12
0  0  15 26 12
0  27 0  0  10
0  0  0  0  21
*/