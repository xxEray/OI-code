#include <bits/stdc++.h>

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
char a[N][N];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m && a[x][y] != 'X'; }

int dis[4][N][N];

int main() {
#ifndef DEBUG
	freopen("mirror.in", "r", stdin);
	freopen("mirror.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	fgets(a[0], N, stdin), memset(a[0], 0, sizeof(a[0]));
	for(int i = 1; i <= n; i++) fgets(a[i] + 1, N - 1, stdin);
	int stx = 0, sty = 0, edx = 0, edy = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(a[i][j] == 'A') stx = i, sty = j, a[i][j] = ' ';
		else if(a[i][j] == 'B') edx = i, edy = j, a[i][j] = ' ';
	for(int i = 0; i < 4; i++) for(int x = 1; x <= n; x++) for(int y = 1; y <= m; y++) dis[i][x][y] = INF;
	std::deque<std::array<int, 3>> q;
	for(int i = 0; i < 4; i++) if(check(stx + dir[i][0], sty + dir[i][1])) dis[i][stx + dir[i][0]][sty + dir[i][1]] = 0, q.push_back({i, stx + dir[i][0], sty + dir[i][1]});
	while(!q.empty()) {
		int d = q.front()[0], x = q.front()[1], y = q.front()[2];
		q.pop_front();
		// printf("%d(%d,%d,%d) | ", dis[d][x][y], d, x, y);
		// for(auto &p : q) printf("%d(%d,%d,%d) ", dis[p[0]][p[1]][p[2]], p[0], p[1], p[2]);
		// puts("");
		auto insert = [&](int td, int tx, int ty, int w) -> void {
			if(!check(tx, ty)) return;
			if(dis[td][tx][ty] > dis[d][x][y] + w) {
				dis[td][tx][ty] = dis[d][x][y] + w;
				if(w) q.push_back({td, tx, ty});
				else q.push_front({td, tx, ty});
			}
		};
		if(a[x][y] == '\\' || a[x][y] == ' ') insert(d ^ 1, x + dir[d ^ 1][0], y + dir[d ^ 1][1], (a[x][y] == ' '));
		if(a[x][y] == '/' || a[x][y] == ' ') insert(d ^ 3, x + dir[d ^ 3][0], y + dir[d ^ 3][1], (a[x][y] == ' '));
		if(a[x][y] == ' ') insert(d, x + dir[d][0], y + dir[d][1], 0);
	}
	int ans = INF;
	for(int i = 0; i < 4; i++) ans = std::min(ans, dis[i][edx][edy]);
	printf("%d\n", ans);
	return 0;
} /*
10 11
XXXXXXXXXXX
X \       X
X    \    X
XA    X XXX
X XX / \  X
X     X X X
X \/ /X / X
X  \  / B X
X\   /\  /X
XXXXXXXXXXX
*/