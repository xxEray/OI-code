#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 1000 + 5;
const int INF = 0x3f3f3f3f;

std::vector<int> to[N][30];
int n, m;

int dis[N][N], vis[N][N];
std::queue<std::pair<int, int>> q;
void bfs() {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = INF;
	q.push({1, n}), dis[1][n] = 0, vis[1][n] = true;
	while(!q.empty()) {
		auto u = q.front();
		int ux = u.first, uy = u.second;
		q.pop();
		for(int c = 0; c < 26; c++) for(int vx : to[ux][c]) for(int vy : to[uy][c]) if(!vis[vx][vy]) {
			dis[vx][vy] = dis[ux][uy] + 2;
			q.push({vx, vy}), vis[vx][vy] = true;
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) printf("dis[(%d, %d)] = %d\n", i, j, dis[hash(i, j)]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v; char c[2];
		scanf("%d%d%s", &u, &v, c);
		to[u][c[0] - 'a'].push_back(v);
		if(u != v) to[v][c[0] - 'a'].push_back(u);
	}
	bfs();
	int ans = INF;
	for(int i = 1; i <= n; i++) ans = std::min(ans, dis[i][i]);
	for(int i = 1; i <= n; i++) for(int c = 0; c < 26; c++) for(int j : to[i][c]) ans = std::min(ans, dis[i][j] + 1);
	if(ans == INF) puts("-1");
	else printf("%d\n", ans);
	return 0;
}