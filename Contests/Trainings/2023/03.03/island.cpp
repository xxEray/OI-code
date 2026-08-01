#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek = 1;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

bool vis[N];
int sz[N], dep[N];
int root, rootwt, allsize;
void getroot(int u, int fa) {
	dep[u] = dep[fa] + 1;
	sz[u] = 1;
	int mx = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(rootwt > mx) root = u, rootwt = mx;
}
int mx[N];
void dfs(int u, int fa) {
	mx[sz[u]] = std::max(mx[sz[u]], dep[u]);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && !vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, u);
	}
}
int t[N], ct[N], ans[N];
void calc(int u) {
	for(int i = 1; i <= sz[u]; i++) t[i] = ct[i] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		for(int j = 1; j <= sz[v]; j++) mx[j] = 0;
		dfs(v, u);
		for(int j = sz[v] - 1; j >= 1; j--) mx[j] = std::max(mx[j], mx[j + 1]);
		for(int j = std::min(sz[v], sz[u] - sz[v]); j >= 1; j--) ans[j * 2] = std::max(ans[j * 2], mx[j]);
		for(int j = sz[v]; j >= 1; j--) {
			if(mx[j] > t[j]) ct[j] = t[j], t[j] = mx[j];
			else if(mx[j] > ct[j]) ct[j] = mx[j];
		}
	}
	for(int i = 1; i <= sz[u] / 2; i++) if(t[i] > 1 && ct[i] > 1) ans[i * 2] = std::max(ans[i * 2], t[i] + ct[i] - 1);
}
void solve(int u) {
	getroot(u, 0), vis[u] = true, calc(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		getroot(v, 0);
		rootwt = INF, allsize = sz[v], getroot(v, 0);
		solve(root);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int i = 1; i <= n; i++) printf("%d\n", std::max(ans[i], 1));
	return 0;
}