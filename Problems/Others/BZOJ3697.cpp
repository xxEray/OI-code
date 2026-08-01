#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }
int n;

bool vis[N];
int size[N];
int root, rootwt, allsize;
void getroot(int u, int fa) {
	int mx = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) {
		int v = edge[i].to;
		getroot(v, u);
		size[u] += size[v];
		mx = std::max(mx, size[v]);
	}
	mx = std::max(mx, allsize - size[u]);
	if(mx < rootwt) root = u, rootwt = mx;
}
template<typename T, int L, int R> struct Array { T a[R - L + 1]; T &operator[](int ind) { return a[ind - L]; } };
Array<LL, -N, N> g1, g[2], g2[2];
LL ans = 0;
int d[N], mxd;
void dfs(int u, LL dis, int fa) {
	d[u] = d[fa] + 1, mxd = std::max(mxd, d[u]);
	g2[(bool)g1[dis]][dis]++;
	g1[dis]++;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) dfs(edge[i].to, dis + edge[i].w, u);
	g1[dis]--;
}
void calc(int u) {
	d[u] = 0;
	int mxall = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		mxd = 0; dfs(v, edge[i].w, 0); mxall = std::max(mxall, mxd);
		ans += g2[0][0] * (g[0][0] + g[1][0]);
		ans += g2[1][0] * (g[0][0] + g[1][0] + 1);
		for(int j = -mxd; j <= mxd; j++) if(j) {
			ans += g2[0][-j] * g[1][j];
			ans += g2[1][-j] * g[0][j];
			ans += g2[1][-j] * g[1][j];
		}
		for(int j = -mxd; j <= mxd; j++) g[0][j] += g2[0][j], g[1][j] += g2[1][j], g2[0][j] = g2[1][j] = 0;
	}
	for(int i = -mxall; i <= mxall; i++) g[0][i] = g[1][i] = 0;
}
void solve(int u) {
	vis[u] = true, calc(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		rootwt = INF, allsize = size[v], getroot(v, 0), solve(root);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); w = (w ? 1 : -1); add_edge(u, v, w), add_edge(v, u, w); }
	rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	printf("%lld\n", ans);
	return 0;
} /*
5
1 2 1
1 3 2
1 4 1
2 5 3
*/