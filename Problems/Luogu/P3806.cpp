#include <bits/stdc++.h>

const int N = 1e4 + 5;
const int M = 100 + 5;
const int MAXV = 1e7 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int q[M];
bool ans[M];

bool vis[N];
int sz[N];
int allsize, root, rootwt;
int tin[MAXV];
void dfs(int u, int fa, int dep, const std::function<void(int)> &func) {
	func(dep);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, dep + edge[i].w, func);
	}
}
void calc(int u) {
	dfs(u, 0, 0, [&](int dep) { if(dep <= 10000000) tin[dep]++; });
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u, edge[i].w, [&](int dep) { if(dep <= 10000000) tin[dep]--; });
		dfs(v, u, edge[i].w, [&](int dep) {
			for(int j = 1; j <= m; j++)
				if(0 <= q[j] - dep && q[j] - dep <= 10000000)
					ans[j] |= tin[q[j] - dep];
		});
		dfs(v, u, edge[i].w, [&](int dep) { if(dep <= 10000000) tin[dep]++; });
	}
	dfs(u, 0, 0, [&](int dep) { if(dep <= 10000000) tin[dep]--; });
}
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		mx = std::max(mx, sz[v]);
		sz[u] += sz[v];
	}
	mx = std::max(mx, allsize - sz[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
void solve(int u) {
	calc(u);
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0), allsize = sz[v], rootwt = INF, getroot(v, 0), solve(root);
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