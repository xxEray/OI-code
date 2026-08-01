#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 10 + 2;
const int INF = 0x3f3f3f3f;

int n, m;
char maze[N][N];
int g[N * N * N * N * N * N], f[N * N * N * N * N * N], d[N * N * N * N * N * N];
bool h[N * N * N * N * N * N];
std::vector<int> to[N * N * N * N * N * N], rev[N * N * N * N * N * N];

int sx1, sy1, sx2, sy2, sx3, sy3;
inline int hash(int x1, int y1, int x2, int y2, int x3, int y3) { return (x1 - 1) * 100000 + (y1 - 1) * 10000 + (x2 - 1) * 1000 + (y2 - 1) * 100 + (x3 - 1) * 10 + y3; }
inline int turn(int x1, int y1, int x2, int y2, int x3, int y3) { return ((x1 ^ sx1 ^ y1 ^ sy1 ^ x2 ^ sx2 ^ y2 ^ sy2) & 1) == ((x3 ^ sx3 ^ y3 ^ sy3) & 1) ? -1 : 1; }
inline bool check(int x1, int y1, int x2, int y2, int x3, int y3) {
	if(x1 == x2 && y1 == y2) return false;
	if(maze[x1][y1] == '#' || maze[x2][y2] == '#' || maze[x3][y3] == '#') return false;
	if(x1 < 1 || x1 > n || y1 < 1 || y1 > m) return false;
	if(x2 < 1 || x2 > n || y2 < 1 || y2 > m) return false;
	if(x3 < 1 || x3 > n || y3 < 1 || y3 > m) return false;
	return true;
}

void init() {
	for(int i = 1; i <= 1000000; i++) to[i].clear(), rev[i].clear(), g[i] = 0, f[i] = -1, h[i] = true, d[i] = 0;
	for(int x1 = 1; x1 <= 10; x1++) for(int y1 = 1; y1 <= 10; y1++)
		for(int x2 = 1; x2 <= 10; x2++) for(int y2 = 1; y2 <= 10; y2++) {
			g[hash(x1, y1, x2, y2, x1, y1)] = -1, f[hash(x1, y1, x2, y2, x1, y1)] = 0;
			g[hash(x1, y1, x2, y2, x2, y2)] = -1, f[hash(x1, y1, x2, y2, x2, y2)] = 0;
			for(int y3 = 1; y3 <= 10; y3++) g[hash(x1, y1, x2, y2, 1, y3)] = turn(x1, y1, x2, y2, 1, y3), f[hash(x1, y1, x2, y2, 1, y3)] = 0;
		}
	for(int x1 = 1; x1 <= 10; x1++) for(int y1 = 1; y1 <= 10; y1++)
		for(int x2 = 1; x2 <= 10; x2++) for(int y2 = 1; y2 <= 10; y2++)
			for(int x3 = 1; x3 <= 10; x3++) for(int y3 = 1; y3 <= 10; y3++) {
				int hu = hash(x1, y1, x2, y2, x3, y3), hv;
				if(g[hu]) continue;
				if(turn(x1, y1, x2, y2, x3, y3) == 1) {
					hv = hash(x1, y1, x2, y2, x3 - 1, y3); if(check(x1, y1, x2, y2, x3 - 1, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2, y2, x3, y3 + 1); if(check(x1, y1, x2, y2, x3, y3 + 1)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2, y2, x3, y3 - 1); if(check(x1, y1, x2, y2, x3, y3 - 1)) to[hu].push_back(hv);
				} else {
					hv = hash(x1 + 1, y1, x2, y2, x3, y3); if(check(x1 + 1, y1, x2, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1 + 1, x2, y2, x3, y3); if(check(x1, y1 + 1, x2, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1 - 1, y1, x2, y2, x3, y3); if(check(x1 - 1, y1, x2, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1 - 1, x2, y2, x3, y3); if(check(x1, y1 - 1, x2, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2 + 1, y2, x3, y3); if(check(x1, y1, x2 + 1, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2, y2 + 1, x3, y3); if(check(x1, y1, x2, y2 + 1, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2 - 1, y2, x3, y3); if(check(x1, y1, x2 - 1, y2, x3, y3)) to[hu].push_back(hv);
					hv = hash(x1, y1, x2, y2 - 1, x3, y3); if(check(x1, y1, x2, y2 - 1, x3, y3)) to[hu].push_back(hv);
				}
			}
	for(int i = 1; i <= 1000000; i++) for(int j : to[i]) d[i]++, rev[j].push_back(i);
	for(int i = 1; i <= 1000000; i++) if(!d[i] && !g[i]) g[i] = -1, f[i] = 0;
}

void topo() {
	std::vector<int> q;
	for(int i = 1; i <= 1000000; i++) if(d[i] == 0) q.push_back(i);
	assert(!q.empty());
	while(!q.empty()) {
		int u = q.back();
		// if(!rev[u].empty()) printf("topo %06d\n", u - 1);
		q.pop_back();
		for(int v : rev[u]) if(d[v]) {
			d[v]--;
			if(g[u] == -1) g[v] = 1;
			if(g[v] != 1) g[v] = -1, h[v] &= (g[u] == 1);
			if(d[v] == 0 || g[v] == 1) {
				d[v] = 0;
				if(g[v] == -1 && !h[v]) g[v] = 0;
				q.push_back(v);
			}
		}
	}
	for(int i = 1; i <= 1000000; i++) if(g[i] == -1 && !h[i]) g[i] = 0;
}

void bfs() {
	
}

int main() {
	int T; scanf("%*d%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%s", maze[i] + 1);
		sx1 = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			if(maze[i][j] == 'O') {
				if(sx1) sx2 = i, sy2 = j;
				else sx1 = i, sy1 = j;
				maze[i][j] = '.';
			} else if(maze[i][j] == 'X')
				sx3 = i, sy3 = j, maze[i][j] = '.';
		init();
		topo();
		for(int i = 1; i <= 1000000; i++) d[i] = 0;
		dfs(hash(sx1, sy1, sx2, sy2, sx3, sy3));
		int vg = g[hash(sx1, sy1, sx2, sy2, sx3, sy3)], vf = f[hash(sx1, sy1, sx2, sy2, sx3, sy3)];
		if(vg == 1) printf("Red %d\n", vf);
		else if(vg == 0) puts("Tie");
		else if(vg == -1) printf("Black %d\n", vf);
		else puts("ERR");
		while(true) {
			int x1, y1, x2, y2, x3, y3;
			printf("< ");
			scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
			printf("> (%d) %d %d\n", turn(x1, y1, x2, y2, x3, y3), g[hash(x1, y1, x2, y2, x3, y3)], f[hash(x1, y1, x2, y2, x3, y3)]);
		}
	}
	return 0;
} /*
0 1
9 9
...######
.#.......
.#######.
.#.#.....
.#O#.####
.#.#.....
.#######.
.#X......
.O.......
*/