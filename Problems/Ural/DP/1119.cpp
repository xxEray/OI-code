#include <cstdio>
#include <cmath>
#include <queue>

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

bool a[N][N];
int n, m, k;

struct Distance {
	int x, y; // x + y √2
	Distance() {}
	Distance(int x_, int y_) : x(x_), y(y_) {}
	double real() const { return x + sqrt(2) * y; }
	bool operator<(const Distance &rhs) const { return real() < rhs.real(); }
	int round() const { return ::round(100.0 * x + sqrt(20000.0) * y); }
};
Distance dis[N][N];

void bfs(int stx, int sty) {
	std::queue<std::pair<int, int> > q;
	q.push({stx, sty});
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		if(x < n && Distance(dis[x][y].x + 1, dis[x][y].y) < dis[x + 1][y])
			q.push({x + 1, y}), dis[x + 1][y] = Distance(dis[x][y].x + 1, dis[x][y].y);
		if(y < m && Distance(dis[x][y].x + 1, dis[x][y].y) < dis[x][y + 1])
			q.push({x, y + 1}), dis[x][y + 1] = Distance(dis[x][y].x + 1, dis[x][y].y);
		if(x < n && y < m && a[x + 1][y + 1] && Distance(dis[x][y].x, dis[x][y].y + 1) < dis[x + 1][y + 1])
			q.push({x + 1, y + 1}), dis[x + 1][y + 1] = Distance(dis[x][y].x, dis[x][y].y + 1);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = true;
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			dis[i][j] = {INF, INF};
	dis[0][0] = {0, 0};
	bfs(0, 0);
	printf("%d\n", dis[n][m].round());
	return 0;
} /*
3 2
3
1 1
3 2
1 2
*/