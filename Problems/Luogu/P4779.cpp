#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, st;
struct Edge { int to, nxt; LL w; } edge[M << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL dis[N];

int main() {
	scanf("%d%d%d", &n, &m, &st);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); add_edge(u, v, w); }
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<>> q;
	for(int i = 1; i <= n; i++) dis[i] = LLINF;
	dis[st] = 0, q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second; LL w = q.top().first;
		q.pop();
		if(dis[u] < w) continue;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to; w = edge[i].w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v});
			}
		}
	}
	for(int i = 1; i <= n; i++) printf("%lld ", dis[i]);
	return 0;
}