#include <cstdio>
#include <vector>
#include <queue>

const int N = 2000 + 5;

const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

#define toint(ch) ((int)((ch) - 'a' + 1))

char a[N][N];
int n, m;
int stx, sty, edx, edy;

struct Point { int x, y; };
std::vector<Point> tos[30];
std::queue<Point> q;

int dis[N][N];

bool visch[30];

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		std::scanf("%s", a[i] + 1);
		for(int j = 1; j <= m; j++) {
			if('a' <= a[i][j] && a[i][j] <= 'z')
				tos[toint(a[i][j])].push_back({i, j});
			else if(a[i][j] == 'S') stx = i, sty = j;
			else if(a[i][j] == 'G') edx = i, edy = j;
		}
	}
	q.push({stx, sty});
	dis[stx][sty] = 1; // dis[][] is also vis[][]
	while(!q.empty()) {
		int px = q.front().x, py = q.front().y;
		char pc = a[px][py];
		q.pop();
		if('a' <= pc && pc <= 'z' && !visch[toint(pc)]) {
			for(const Point &d : tos[toint(pc)]) {
				int dx = d.x, dy = d.y;
				if(!(1 <= dx && dx <= n && 1 <= dy && dy <= m && a[dx][dy] != '#' && !dis[dx][dy])) continue;
				dis[dx][dy] = dis[px][py] + 1;
				q.push({dx, dy});
			}
			visch[toint(pc)] = true;
		}
		for(int i = 0; i < 4; i++) {
			int dx = px + d[i][0], dy = py + d[i][1];
			if(!(1 <= dx && dx <= n && 1 <= dy && dy <= m && a[dx][dy] != '#' && !dis[dx][dy])) continue;
			dis[dx][dy] = dis[px][py] + 1;
			q.push({dx, dy});
		}
	}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 1; j <= m; j++)
	// 		std::printf("%2d%c", dis[i][j] - 1, j == m ? '\n' : ' ');
	std::printf("%d\n", (dis[edx][edy] == 0 ? -1 : dis[edx][edy] - 1));
	return 0;
}