#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt; LL w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, LL w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++;}
int n, m;

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

int ans = INF;
int t[1000005], g[1000005];
std::vector<int> stk, allstk;
void dfs(int u, int dis, int d, int fa) {
	if(dis <= 1000000) {
		if(t[dis]) t[dis] = std::min(t[dis], d);
		else stk.push_back(dis), t[dis] = d;
	}
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to] && edge[i].to != fa) dfs(edge[i].to, dis + edge[i].w, d + 1, u);
}
void calc(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs(v, edge[i].w, 1, 0);
		if(t[m]) ans = std::min(ans, t[m]);
		for(int j : stk) {
			if(g[m - j]) ans = std::min(ans, g[m - j] + t[j]);
			g[j] = (g[j] ? std::min(g[j], t[j]) : t[j]), t[j] = 0;
			allstk.push_back(j);
		}
		stk.clear();
	}
	for(int x : allstk) g[x] = 0;
	allstk.clear();
}
void solve(int u) {
	vis[u] = true, calc(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		rootwt = INF, allsize = size[v], getroot(v, 0), solve(root);
	}
}

inline LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); u++, v++; add_edge(u, v, w), add_edge(v, u, w); }
	rootwt = INF, allsize = n, getroot(1, 0), solve(root);
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
} /*
5
1 2 1
1 3 2
1 4 1
2 5 3
*/