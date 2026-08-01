#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 1e5 + 5;
const int K = 18;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}

int qs[N];
int n, m, k;

int dis[K][N];

void bfs(int st) {
	std::queue<int> q;
	q.push(qs[st]);
	for (int i = 1; i <= n; i++) dis[st][i] = INF;
	dis[st][qs[st]] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = edge[i].nxt)
			if (dis[st][edge[i].to] > dis[st][u] + 1) {
				dis[st][edge[i].to] = dis[st][u] + 1;
				q.push(edge[i].to);
			}
	}
}

int f[1 << K][K];

int main() {
	std::scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		std::scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	std::scanf("%d", &k);
	for (int i = 1; i <= k; i++) std::scanf("%d", &qs[i]);
	for (int i = 1; i <= k; i++) bfs(i);
	int U = (1 << k) - 1;
	for (int i = 1; i <= U; i++)
		for (int j = 1; j <= k; j++)
			f[i][j] = INF;
	for (int i = 1; i <= k; i++) f[(1 << (i - 1))][i] = 0;
	for (int s = 1; s <= U; s++)
		for (int i = 1; i <= k; i++)
			if (s & (1 << (i - 1)))
				for (int j = 1; j <= k; j++) {
					if (s & (1 << (j - 1))) continue;
					f[s | (1 << (j - 1))][j] = std::min(f[s | (1 << (j - 1))][j], f[s][i] + dis[i][qs[j]]);
				}
	int ans = INF;
	for (int i = 1; i <= k; i++)
		ans = std::min(ans, f[U][i]);
	std::printf("%d\n", (ans == INF ? -1 : ans + 1));
	return 0;
}