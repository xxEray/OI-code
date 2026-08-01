#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int a[N], b[N];
int n, m;

int f[N][N];

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) std::scanf("%d", &b[i]);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			f[i][j] = INF;
	f[0][0] = 0;
	for(int i = 1; i <= n; i++) f[i][0] = i;
	for(int i = 1; i <= m; i++) f[0][i] = i;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + (a[i] != b[j]));
			f[i][j] = std::min(f[i][j], f[i - 1][j] + 1);
			f[i][j] = std::min(f[i][j], f[i][j - 1] + 1);
		}
	// std::puts("-----");
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= m; j++)
	// 		std::printf("%d%c", f[i][j], j == m ? '\n' : ' ');
	// std::puts("-----");
	std::printf("%d\n", f[n][m]);
	return 0;
}