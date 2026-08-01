#include <cstdio>
#include <vector>
#include <queue>

const int INF = 0x3f3f3f3f;
const int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};

char **a;
int **dis;

int n, m, k;

int stx, sty, edx, edy;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	a = new char *[n + 5];
	for(int i = 0; i < n + 5; i++) {
		a[i] = new char[m + 5];
		for(int j = 0; j < m + 5; j++) a[i][j] = 0;
	}
	dis = new int *[n + 5];
	for(int i = 0; i < n + 5; i++) {
		dis[i] = new int[m + 5];
		for(int j = 0; j < m + 5; j++) dis[i][j] = INF;
	}
	scanf("%d%d%d%d", &stx, &sty, &edx, &edy);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	std::queue<std::pair<int, int>> q;
	dis[stx][sty] = 0;
	q.push({stx, sty});
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++)
			for(int j = 1; j <= k; j++) {
				int dx = x + dir[i][0] * j;
				int dy = y + dir[i][1] * j;
				if(dx < 1 || dx > n || dy < 1 || dy > m || a[dx][dy] == '@' || dis[dx][dy] <= dis[x][y]) break;
				if(dis[dx][dy] <= dis[x][y] + 1) continue;
				dis[dx][dy] = dis[x][y] + 1;
				q.push({dx, dy});
			}
	}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= m; j++)
	// 		printf("%2d%c", dis[i][j] == INF ? -1 : dis[i][j], j == m ? '\n' : ' ');
	printf("%d\n", dis[edx][edy] == INF ? -1 : dis[edx][edy]);
	return 0;
}