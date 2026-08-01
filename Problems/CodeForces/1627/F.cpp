#include <cstdio>
#include <algorithm>
#include <queue>
#include <array>
#include <assert.h>
using std::min;
using std::max;
using std::abs;

const int N = 500 + 5;
const int INF = 0x3f3f3f3f;

int n, m;

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int w[N][N][4];
int dis[N][N];
bool inq[N][N];
#define Data std::array<int, 3>
std::priority_queue<Data, std::vector<Data>, std::greater<Data>> q;
void spfa(int stx, int sty) {
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) dis[i][j] = INF, inq[i][j] = false;
	dis[stx][sty] = 0;
	q.push({dis[stx][sty], stx, sty}), inq[stx][sty] = true;
	while(!q.empty()) {
		int x = q.top()[1], y = q.top()[2];
		q.pop();
		if(!inq[x][y]) continue;
		inq[x][y] = false;
		for(int i = 0; i < 4; i++) {
			int dx = x + dir[i][0], dy = y + dir[i][1];
			if(!(0 <= dx && dx <= n && 0 <= dy && dy <= n)) continue;
			if(dis[dx][dy] > dis[x][y] + w[x][y][i]) {
				dis[dx][dy] = dis[x][y] + w[x][y][i];
				// printf("(%d, %d)[=%d] + %d -> (%d, %d)\n", x, y, dis[x][y], w[x][y][i], dx, dy);
				q.push({dis[dx][dy], dx, dy}), inq[dx][dy] = true;
			}
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k < 4; k++) w[i][j][k] = 0;
		for(int i = 1; i <= m; i++) {
			int r1, c1, r2, c2;
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			// assert(abs(r1 - r2) + abs(c1 - c2) == 1);
			if(r1 > r2) std::swap(r1, r2);
			if(c1 > c2) std::swap(c1, c2);
			if(r1 == r2) w[r1 - 1][c1][1]++, w[r1][c1][3]++;
			if(c1 == c2) w[r1][c1 - 1][0]++, w[r1][c1][2]++;
			r1 = n + 1 - r1, c1 = n + 1 - c1, r2 = n + 1 - r2, c2 = n + 1 - c2;
			if(r1 > r2) std::swap(r1, r2);
			if(c1 > c2) std::swap(c1, c2);
			if(r1 == r2) w[r1 - 1][c1][1]++, w[r1][c1][3]++;
			if(c1 == c2) w[r1][c1 - 1][0]++, w[r1][c1][2]++;
		}
		// for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k < 4; k++)
		// 	if(w[i][j][k]) printf("w[%d][%d][%d] = %d\n", i, j, k, w[i][j][k]);
		spfa(0, 0);
		printf("%d\n", m - dis[n / 2][n / 2]);
	}
	return 0;
} /*
3
8 4
1 2 1 3
2 2 2 3
3 2 3 3
4 2 4 3
1 4 2 4
2 1 3 1
2 2 3 2
4 1 4 2
7 2
1 1 1 2
1 1 1 2
1 1 2 1
1 1 2 1
1 2 2 2
1 2 2 2
2 1 2 2
1 6
3 3 3 4
*/