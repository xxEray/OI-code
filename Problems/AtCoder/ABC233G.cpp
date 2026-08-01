#include <cstdio>
#include <algorithm>

#define x0 x314124351221
#define y1 y341242135415

const int N = 50 + 5;

int f[N][N][N][N];
int a[N][N];
int n;

int pre[N][N];
int sum(int i, int j, int r, int c) { return pre[r][c] - pre[i - 1][c] - pre[r][j - 1] + pre[i - 1][j - 1]; }

void chkmin(int &x, int y) { y < x ? x = y : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) { char s[2]; scanf("%1s", s); a[i][j] = (s[0] == '#' ? 1 : 0); }
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
	for(int lx = 1; lx <= n; lx++)
		for(int ly = 1; ly <= n; ly++)
			for(int i = 1; i + lx - 1 <= n; i++)
				for(int j = 1; j + ly - 1 <= n; j++) {
					int r = i + lx - 1, c = j + ly - 1;
					f[i][j][r][c] = std::max(lx, ly);
					for(int k = i; k <= r; k++) if(sum(k, j, k, c) == 0) chkmin(f[i][j][r][c], f[i][j][k - 1][c] + f[k + 1][j][r][c]);
					for(int k = j; k <= c; k++) if(sum(i, k, r, k) == 0) chkmin(f[i][j][r][c], f[i][j][r][k - 1] + f[i][k + 1][r][c]);
				}
	printf("%d\n", f[1][1][n][n]);
	return 0;
}