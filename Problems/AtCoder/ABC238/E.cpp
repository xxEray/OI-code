#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 2e5 + 6;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n, m;

int vis[N];
std::queue<int> q;
void bfs(int st) {
	q.push(st);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
			int v = edge[i].to;
			q.push(v), vis[v] = true;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); add_edge(x, y + 1), add_edge(y + 1, x); }
	bfs(1);
	puts(vis[n + 1] ? "Yes" : "No");
	return 0;
}