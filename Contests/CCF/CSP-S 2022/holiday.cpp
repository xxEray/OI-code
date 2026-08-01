#include <bits/stdc++.h>

typedef long long LL;
typedef __int128_t Lint;

const int N = 2500 + 5;
const int M = 1e4 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
LL a[N];
struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dis[N][N];
bool vis[N];
std::queue<int> q;
void bfs(int st) {
	while(!q.empty()) q.pop();
	for(int i = 1; i <= n; i++) vis[i] = false, dis[st][i] = INF;
	dis[st][st] = 0, vis[st] = true, q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(vis[v]) continue;
			dis[st][v] = dis[st][u] + 1, vis[v] = true, q.push(v);
		}
	}
}

bool e[N][N];
int r[N][3];

void print(Lint x) {
	char stk[200]; int top = 0;
	if(x == 0) stk[top++] = '0';
	while(x) stk[top++] = x % 10 + '0', x /= 10;
	for(top--; top >= 0; top--) putchar(stk[top]);
}

int main() {
#ifndef DEBUG
	freopen("holiday.in", "r", stdin);
	freopen("holiday.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 2; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) bfs(i);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = (i == j ? false : dis[i][j] <= K + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) if(e[1][j] && e[j][i] && (r[i][0] == 0 || a[r[i][0]] < a[j])) r[i][0] = j;
		for(int j = 1; j <= n; j++) if(e[1][j] && e[j][i] && j != r[i][0] && (r[i][1] == 0 || a[r[i][1]] < a[j])) r[i][1] = j;
		for(int j = 1; j <= n; j++) if(e[1][j] && e[j][i] && j != r[i][0] && j != r[i][1] && (r[i][2] == 0 || a[r[i][2]] < a[j])) r[i][2] = j;
//		printf("%d: %d %d %d\n", i, r[i][0], r[i][1], r[i][2]);
	}
	Lint ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(e[i][j]) {
		int x1 = r[i][0], x2 = r[i][1], y1 = r[j][0], y2 = r[j][1];
		if(x1 == j) x1 = r[i][1], x2 = r[i][2];
		else if(x2 == j) x2 = r[i][2];
		if(y1 == i) y1 = r[j][1], y2 = r[j][2];
		else if(y2 == i) y2 = r[j][2];
//		printf("%d %d (%d, %d) (%d, %d)!\n", i, j, x1, x2, y1, y2);
		if(x1 != y1) {
			if(x1 && y1) ans = std::max(ans, (Lint)a[i] + a[j] + a[x1] + a[y1]);
		} else {
			if(x1 && y2) ans = std::max(ans, (Lint)a[i] + a[j] + a[x1] + a[y2]);
			if(x2 && y1) ans = std::max(ans, (Lint)a[i] + a[j] + a[x2] + a[y1]);
		}
//		printf("i = %d, j = %d, ans = %d\n", i, j, (int)ans);
	}
	print(ans), printf("\n");
	return 0;
} /*
7 9 0
1 1 1 2 3 4
1 2
2 3
3 4
1 5
1 6
1 7
5 4
6 4
7 4
*/
