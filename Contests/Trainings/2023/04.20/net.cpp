#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>

const int N = 2500 + 5;
const int INF = 0x3f3f3f3f;

int n;
char s[N];
int a[N][N];
std::bitset<N> b[N], far[N];

int dis[N][N];
void bfs(int st) {
	std::bitset<N> todo, nxt;
	std::queue<int> q;
	for(int i = 1; i <= n; i++) todo[i] = 1, dis[st][i] = INF;
	todo[st] = 0, dis[st][st] = 0, q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		nxt = todo & b[u];
		for(int v = nxt._Find_first(); v != (int)nxt.size(); v = nxt._Find_next(v)) {
			dis[st][v] = dis[st][u] + 1;
			todo[v] = 0;
			q.push(v);
		}
	}
}

bool vis[N];
int f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for(int j = 1; j <= n; j++) a[i][j] = s[j] - '0', b[i][j] = a[i][j];
	}
	for(int i = 1; i <= n; i++) bfs(i);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f[i] = std::max(f[i], dis[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(dis[i][j] == f[i]) far[i][j] = 1;
	int mn = INF;
	for(int i = 1; i <= n; i++) mn = std::min(mn, f[i]);
	int cx = 0, cy = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(i != j && a[i][j] && f[i] == mn && f[j] == mn) {
			if((far[i] & far[j]).any()) continue;
			cx = i, cy = j;
			break;
		}
	if(!cy) for(int i = 1; i <= n; i++) if(f[i] == mn) { cx = i; break; }
	// printf("cx = %d, cy = %d\n", cx, cy);
	// for(int i = 1; i <= n; i++) printf("dis[%d] = %d, %d\n", i, dis[cx][i], dis[cy][i]);
	vis[cx] = true;
	if(cy) vis[cy] = true, printf("%d %d\n", cx, cy);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(a[i][j] && !vis[j]) {
			bool flag = false;
			flag |= (!cy && dis[cx][i] + 1 == dis[cx][j]);
			flag |= (cy && dis[cx][i] <= dis[cy][i] && dis[cx][j] <= dis[cy][j] && dis[cx][i] + 1 == dis[cx][j]);
			flag |= (cy && dis[cy][i] <= dis[cx][i] && dis[cy][j] <= dis[cx][j] && dis[cy][i] + 1 == dis[cy][j]);
			if(!flag) continue;
			printf("%d %d\n", i, j), vis[j] = true;
		}
	return 0;
}