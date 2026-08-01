#include <cstdio>
#include <algorithm>

const int N = 200 + 5;

char a[2][N][N];
int n, m;

inline bool is(char c1, char c2) { return c1 == c2 || c1 == 'X'; }
inline void minus(char &c, char c2) { c = (c == 'X' ? (c2 == '/' ? '\\' : '/') : '.'); }

int dfs(int x, int y, int t) {
	// printf("(%d, %d, %d)\n", x, y, t);
	if(x < 1 || x > n || y < 1 || y > m) return 0;
	bool fl = false;
	if(is(a[t][x][y], '\\')) minus(a[t][x][y], '\\'), dfs(x - 1, y - 1, !t), fl = true;
	if(is(a[t][x][y + 1], '/')) minus(a[t][x][y + 1], '/'), dfs(x - 1, y + 1, !t), fl = true;
	if(is(a[t][x + 1][y], '/')) minus(a[t][x + 1][y], '/'), dfs(x + 1, y - 1, !t), fl = true;
	if(is(a[t][x + 1][y + 1], '\\')) minus(a[t][x + 1][y + 1], '\\'), dfs(x + 1, y + 1, !t), fl = true;
	return fl;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[0][i] + 1);
	for(int i = 1; i <= n; i++) scanf("%s", a[1][i] + 1);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= 1; k++) {
				int ret = dfs(i, j, k);
				if(ret) {
					cnt += ret;
					// puts("------");
					// for(int r = 1; r <= n; r++) printf("%s\n", a[0][r] + 1);
					// puts("");
					// for(int r = 1; r <= n; r++) printf("%s\n", a[1][r] + 1);
				}
			}
	printf("%d\n", cnt);
	return 0;
}