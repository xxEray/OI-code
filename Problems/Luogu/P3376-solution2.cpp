#include <bits/stdc++.h>

typedef long long LL;

const int N = 200 + 5;
const int M = 5000 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
struct Edge { int to, nxt; LL r; } edge[M << 1];
int head[N];
void add_edge(int u, int v, LL c) { static int k = 2; edge[k] = (Edge){v, head[u], c}, head[u] = k++; }

int src, dst;

int dep[N], cur[N];
bool bfs() {
	for(int i = 1; i <= n; i++) dep[i] = INF;
	std::queue<int> q;
	dep[src] = 0, q.push(src);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].r && dep[edge[i].to] == INF) {
			int v = edge[i].to;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
	for(int i = 1; i <= n; i++) cur[i] = head[i];
	return dep[dst] != INF;
}

LL dfs(int u, LL in) {
	if(u == dst) return in;
	LL out = 0;
	for(int &i = cur[u]; i; i = edge[i].nxt) if(edge[i].r && dep[edge[i].to] == dep[u] + 1) {
		int v = edge[i].to;
		LL ret = dfs(v, std::min(in, edge[i].r));
		edge[i].r -= ret, edge[i ^ 1].r += ret;
		in -= ret, out += ret;
		if(!in) return out;
	}
	if(!out) dep[u] = INF;
	return out;
}

void dinic() {
	LL ans = 0;
	while(bfs()) ans += dfs(src, LLINF);
	printf("%lld\n", ans);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &src, &dst);
	for(int i = 1; i <= m; i++) { int u, v, c; scanf("%d%d%d", &u, &v, &c); add_edge(u, v, c), add_edge(v, u, 0); }
	dinic();
	return 0;
}