#include <cstdio>
#include <algorithm>

const int N = 2e4 + 5;
const int M = 1e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], low[N], vis[N];
int time_stamp;
bool iscut[N];
int root;
void tarjan(int u) {
	vis[u] = 1;
	low[u] = dfn[u] = ++time_stamp;
	int chld = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) {
			chld++;
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if(u != root && low[v] >= dfn[u]) iscut[u] = true;
		} else if(vis[v] == 1) {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if(u == root && chld > 1) iscut[u] = true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); if(u != v) add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(root = i);
	// for(int i = 1; i <= n; i++) printf("%d: %d %d\n", i, dfn[i], low[i]);
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += iscut[i];
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) if(iscut[i]) printf("%d ", i);
	return 0;
}