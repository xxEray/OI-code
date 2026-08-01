#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int M = 4e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N], e[N][2];

struct Edge { int to, nxt; } edge[M << 1];
int head[N], ek = 1;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
int dis1[N], disn[N];
bool vis[N];
void dijkstra(int st, int *dis) {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
	assert(a[st] == 0);
	for(int i = 1; i <= n; i++) vis[i] = false, dis[i] = INF;
	dis[st] = 0;
	q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] > std::max(a[v], dis[u] + 1)) {
				dis[v] = std::max(a[v], dis[u] + 1);
				q.push({dis[v], v});
			}
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dijkstra(1, dis1), dijkstra(n, disn);
	int ans = INF;
	for(int i = 1; i <= n; i++) ans = std::min(ans, dis1[i] + disn[i] + std::abs(dis1[i] - disn[i]));
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		ans = std::min(ans, dis1[u] + disn[v] + std::max(1, std::abs(dis1[u] - disn[v])));
	}
	printf("%d\n", ans);
	return 0;
}