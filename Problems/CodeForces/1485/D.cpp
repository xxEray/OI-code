#include <cstdio>

const int N = 500 + 5;

int a[N][N];
int n, m;

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			std::scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			std::printf("%d%c", (((i + j) & 1) ? 720720 : 720720 + a[i][j] * a[i][j] * a[i][j] * a[i][j]), j == m ? '\n' : ' ');
	return 0;
}