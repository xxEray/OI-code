#include <cstdio>
#include <algorithm>

typedef unsigned char byte;

const int N = 150 + 5;
const byte INF = 255;

bool a[N][N];
int n, m;
byte f[N][N][N][N], g[N][N][N][N], h[N][N][N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) { char tmp[2]; scanf("%1s", tmp); a[i][j] = (tmp[0] == '#' ? true : false); }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		f[i][j][i - 1][j - 1] = INF, g[i][j][i - 1][j - 1] = i - 1, h[i][j][i - 1][j - 1] = j - 1;
	for(int li = 1; li <= n; li++) for(int lj = 1; lj <= m; lj++) for(int i = 1; i + li - 1 <= n; i++) for(int j = 1; j + lj - 1 <= m; j++) {
		int r = i + li - 1, c = j + lj - 1;
		if(f[i][j][r - 1][c] == 0 && f[r][j][r][c] == 0 && f[i][j][r][c - 1] == 0 &&
			f[i][c][r][c] == 0 && (j == c || a[r][c] == a[r][c - 1]) && (i == r || a[r][c] == a[r - 1][c]))
			{ f[i][j][r][c] = 0, g[i][j][r][c] = r, h[i][j][r][c] = c; continue; }
		f[i][j][r][c] = INF, g[i][j][r][c] = r, h[i][j][r][c] = c;
		byte ret1 = INF, ret2 = INF;
		int p = g[i][j][r - 1][c];
		if(!p) p = i;
		while(p <= r && std::max(f[i][j][p][c], f[p + 1][j][r][c]) + 1 <= ret1)
			ret1 = std::max(f[i][j][p][c], f[p + 1][j][r][c]) + 1, g[i][j][r][c] = p, p++;
		p = h[i][j][r][c - 1];
		if(!p) p = j;
		while(p <= c && std::max(f[i][j][r][p], f[i][p + 1][r][c]) + 1 <= ret2) ret2 = std::max(f[i][j][r][p], f[i][p + 1][r][c]) + 1, h[i][j][r][c] = p, p++;
		f[i][j][r][c] = std::min(ret1, ret2);
	}
	printf("%d\n", (int)f[1][1][n][m]);
	// while(true) {
	// 	int i, j, r, c; scanf("%d%d%d%d", &i, &j, &r, &c);
	// 	printf("%d %d %d %d -> %d, %d, %d\n", i, j, r, c, f[i][j][r][c], g[i][j][r][c], h[i][j][r][c]);
	// }
	return 0;
} /*
3 3
...
.##
.##

6 7
.####.#
#....#.
#....#.
#....#.
.####.#
#....##
*/