#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Edge { int to, nxt; } edge[N << 1];
int head[N], edgek;
void add_edge(int u, int v) { edge[edgek] = (Edge){v, head[u]}, head[u] = edgek++; }
int n, m, A, B, C;

LL w[N], prew[N];

std::queue<int> q;
int dis[N][3];
bool vis[N];
void bfs(int st, int id) {
	for(int i = 1; i <= n; i++) vis[i] = false;
	dis[st][id] = 0, q.push(st), vis[st] = true;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
			int v = edge[i].to;
			dis[v][id] = dis[u][id] + 1;
			vis[v] = true, q.push(v);
		}
	}
}

LL calc(int x, int y) { return x + y > m ? LLINF : 2 * prew[x] + prew[x + y] - prew[x];}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		edgek = 1;
		scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i <= m; i++) scanf("%lld", &w[i]);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		bfs(B, 0), bfs(A, 1), bfs(C, 2);
		std::sort(w + 1, w + m + 1);
		for(int i = 1; i <= m; i++) prew[i] = prew[i - 1] + w[i];
		LL ans = LLINF;
		for(int i = 1; i <= n; i++) ans = std::min(ans, calc(dis[i][0], dis[i][1] + dis[i][2]));
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
4 5 4 2 4
1 5 5 5 5
1 3
2 3
4 2
1 2
1 4
*/