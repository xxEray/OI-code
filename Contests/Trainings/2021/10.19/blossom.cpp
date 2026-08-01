#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 20 + 3;

const int dir[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 2}, {2, 0}, {0, -2}, {-2, 0}};

int n, r1, c1, r2, c2;

struct State { int ra, ca, rb, cb; };
int mf[N][N][N][N]; // dis
bool mg[N][N][N][N]; // vis_once
bool mcd[N][N][N][N]; // calc_ed
#define f(x) (mf[(x).ra][(x).ca][(x).rb][(x).cb])
#define g(x) (mg[(x).ra][(x).ca][(x).rb][(x).cb])
#define cd(x) (mcd[(x).ra][(x).ca][(x).rb][(x).cb])
inline bool check(State x) { return 1 <= x.ra && x.ra <= n && 1 <= x.ca && x.ca <= n && 1 <= x.rb && x.rb <= n && 1 <= x.cb && x.cb <= n; }
inline bool complete(State x) {
	for(int i = 0; i < 4; i++) {
		State v = (State){x.ra + dir[i][0], x.ca + dir[i][1], x.rb, x.cb};
		if(check(v) && !g(v)) { printf("g(%d %d %d %d) is false\n", v.ra, v.ca, v.rb, v.cb); return false; }
	}
	return true;
}
std::queue<State> q;

int main() {
	scanf("%d%d%d%d%d", &n, &r1, &c1, &r2, &c2);
	if(std::abs(r1 - r2) + std::abs(c1 - c2) == 1) { puts("YUYUKO 1"); return 0; }
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			mg[i][j][i][j] = true, mcd[i][j][i][j] = true, q.push((State){i, j, i, j});
	while(!q.empty()) {
		State u = q.front();
		printf("bfs %d %d %d %d\n", u.ra, u.ca, u.rb, u.cb);
		q.pop();
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 8; j++) {
				State v = (State){u.ra + dir[i][0], u.ca + dir[i][1], u.rb + dir[j][0], u.cb + dir[j][1]};
				if(!check(v) || cd(v)) continue;
				g(v) = true, printf("g(%d %d %d %d) = true\n", v.ra, v.ca, v.rb, v.cb);
				if(complete(v)) f(v) = f(u) + 2, cd(v) = true, q.push(v);
			}
	}
	printf("YUKARI %d\n", mf[r1][c1][r2][c2]);
	return 0;
} /*
8 5 4 1 1

*/
