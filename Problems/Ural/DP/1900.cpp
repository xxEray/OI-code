#include <cstdio>
#include <algorithm>

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int a[N][N];
int n, m;

int g[N][N], f[N][N], last[N][N];

void print(int i, int j) {
	if(j > 1) print(last[i][j], j - 1);
	printf("%d ", i - 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = n; j >= i + 1; j--)
			g[i][j] = g[i - 1][j] + g[i][j + 1] - g[i - 1][j + 1] + a[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			f[i][j] = -INF;
			for(int k = 1; k <= i - 1; k++)
				if(f[i][j] < f[k][j - 1] + g[i - 1][i] - g[k - 1][i]) {
					f[i][j] = f[k][j - 1] + g[i - 1][i] - g[k - 1][i];
					last[i][j] = k;
				}
		}
	int ans = 1;
	for(int i = 2; i <= n; i++) if(f[i][m] > f[ans][m]) ans = i;
	// for(int i = 1; i <= n; i++)
	// 	for(int j = i; j <= n; j++)
	// 		printf("Σa[%d .. %d][%d .. %d] = %d\n", i, j, j + 1, n, g[j][j + 1] - g[i - 1][j + 1]);
	printf("%d\n", f[ans][m]);
	print(ans, m);
	return 0;
} /*
4 2
  9 2 1
    6 3
      8

23
1 3
*/