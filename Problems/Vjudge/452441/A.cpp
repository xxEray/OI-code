#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 600 + 5;

int n, m;
int dis1, dis2;

const int color[4][2] = {1, 1, 1, 2, 2, 1, 2, 2};
struct Point { int x, y; };
std::vector<Point> D1, D2;
int a[N][N], b[N][N];

void dfs(int t[][N], int x, int y, int c, const std::vector<Point> &nxt) {
	if(x < 1 || x > n || y < 1 || y > n) return;
	if(t[x][y]) return;
	t[x][y] = c;
	for(int i = -1; i <= 1; i += 2)
		for(int j = -1; j <= 1; j += 2)
			for(int k = 0; k < (int)nxt.size(); k++)
				dfs(t, x + nxt[k].x * i, y + nxt[k].y * j, 3 - c, nxt);
}

int main() {
	// freopen("A.out", "w", stdout);
	scanf("%d%d%d", &n, &dis1, &dis2);
	m = n * n, n = 2 * n;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++) {
			if(i * i + j * j == dis1) D1.push_back({i, j});
			if(i * i + j * j == dis2) D2.push_back({i, j});
		}
	// for(int i = 0; i < (int)D1.size(); i++) printf("%d %d, ", D1[i].x, D1[i].y);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dfs(a, i, j, 1, D1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dfs(b, i, j, 1, D2);
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= n; j++) {
	// 		printf("a[%d][%d] = %d\n", i, j, a[i][j]);
	// 		printf("b[%d][%d] = %d\n", i, j, b[i][j]);
	// 	}
	int ans[4] = {};
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 0; k < 4; k++)
				ans[k] += (a[i][j] == color[k][0] && b[i][j] == color[k][1]);
	int id = 0, cnt = 0;
	for(int k = 0; k < 4; k++) if(ans[k] >= m) id = k;
	for(int i = 1; i <= n && cnt < m; i++)
		for(int j = 1; j <= n && cnt < m; j++)
			if(a[i][j] == color[id][0] && b[i][j] == color[id][1])
				printf("%d %d\n", i - 1, j - 1), cnt++;
	return 0; 
} /*
300 48200 36864
300 86528 8192
*/