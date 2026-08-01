#include <cstdio>
#include <algorithm>

const int N = 250 + 5;

int n, m;
char s[N][N];

unsigned char f[17][N][N][N];

void chkmax(unsigned char &x, unsigned char y) { if(x < y) x = y; }

int main() {
#ifndef DEBUG
	freopen("painting.in", "r", stdin);
	freopen("painting.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int k = m; k >= 1; k--) for(int i = 1; i <= n; i++) {
		bool flag = true;
		for(int j = i; j <= n; j++) {
			if(flag && s[i][k] == s[i][k + 1]) f[0][k][i][j] = f[0][k + 1][i][j];
			else if(flag) f[0][k][i][j] = k;
			else f[0][k][i][j] = k - 1;
			flag &= s[j][k] == s[j + 1][k];
		}
	}
	for(int r = 1; r <= 16; r++) for(int k = m; k >= 1; k--) {
		for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) {
			chkmax(f[r][k][i][j], f[r - 1][k][i][j]);
			chkmax(f[r][k][i][j], f[r - 1][f[r - 1][k][i][j] + 1][i][j]);
		}
		for(int i = 1; i <= n; i++) {
			int p = i;
			for(int j = i + 1; j <= n; j++) {
				while(p <= j - 2 && std::min(f[r - 1][k][i][p], f[r - 1][k][p + 1][j]) <= std::min(f[r - 1][k][i][p + 1], f[r - 1][k][p + 2][j])) p++;
				chkmax(f[r][k][i][j], std::min(f[r - 1][k][i][p], f[r - 1][k][p + 1][j]));
			}
		}
	}
	for(int r = 0; r <= 16; r++) if(f[r][1][1][n] == m) { printf("%d\n", r); break; }
//	while(true) {
//		printf("> ");
//		int i, j, k, r;
//		scanf("%d%d%d%d", &i, &j, &k, &r);
//		printf("< %hd\n", f[i][j][k][r]);
//	}
	return 0;
} /*
3 3
.#.
#.#
.#.
*/
