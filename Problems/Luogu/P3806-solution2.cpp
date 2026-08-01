#include <bits/stdc++.h>

const int N = 1e4 + 5;
const int M = 100 + 5;
const int V = 1e7;
const int MAXV = V + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }
int q[M], ans[M];

bool vis[N];
int sz[N], allsize, root, rootwt;
void getroot(int u, int fa) {
	sz[u] = 1;
	int mx = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		sz[u] += sz[v], mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) root = u, rootwt = mx;
}
int tin[MAXV];
void dfs(int u, int fa, int depth, std::function<void(int)> func) {
	func(depth);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, depth + edge[i].w, func);
	}
}
void calc(int u) {
	// printf("calc %d\n", u);
	dfs(u, 0, 0, [&](int depth) { if(depth <= V) tin[depth]++; });
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, edge[i].w, [&](int depth) { if(depth <= V) tin[depth]--; });
		dfs(v, u, edge[i].w, [&](int depth) {
			for(int j = 1; j <= m; j++) if(0 <= q[j] - depth && q[j] - depth <= V) ans[j] += tin[q[j] - depth];
		});
		dfs(v, u, edge[i].w, [&](int depth) { if(depth <= V) tin[depth]++; });
	}
	dfs(u, 0, 0, [&](int depth) { if(depth <= V) tin[depth]--; });
}
void solve(int u) {
	calc(u);
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u), allsize = sz[v], rootwt = INF, getroot(v, u), solve(root);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= m; i++) scanf("%d", &q[i]);
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int i = 1; i <= m; i++) puts(ans[i] ? "AYE" : "NAY");
	return 0;
}