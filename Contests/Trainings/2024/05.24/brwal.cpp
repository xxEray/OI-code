#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 2e5 + 55;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL K;
struct Graph {
	struct Edge { int to, nxt; } edge[M << 1];
	int head[N], ek;
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
	Graph() : ek(1) {}
} Go, G;
int lim[N];
struct Value {
	LL k, b;
	LL at(LL x) { return k * x + b; }
} a[N];

bool visdfs[N];
std::vector<std::pair<int, int>> extra;
void dfs(int u, int fa) {
	visdfs[u] = true;
	for(int i = Go.head[u]; i; i = Go.edge[i].nxt) if(Go.edge[i].to != fa) {
		int v = Go.edge[i].to;
		if(visdfs[v]) {
			if(u < v) extra.emplace_back(u, v);
			continue;
		}
		G.add_edge(u, v), G.add_edge(v, u);
		dfs(v, u);
	}
}

bool vistc[N];
int sz[N], allsize, root, rootwt;
void getroot(int u, int fa) {
	int mx = 0;
	sz[u] = 1;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) if(G.edge[i].to != fa && !vistc[G.edge[i].to]) {
		int v = G.edge[i].to;
		getroot(v, u);
		sz[u] += sz[v];
		mx = std::max(mx, sz[v]);
	}
	mx = std::max(mx, allsize - sz[u]);
	if(mx < rootwt) rootwt = mx, root = u;
}
std::vector<std::pair<int, int>> refer[N], dots[M];
int now[M];
int viscalc[N], depcalc[N];
int cnt;
void calc(int rt) {
	cnt++;
	std::queue<int> q;
	viscalc[rt] = cnt, depcalc[rt] = 0, q.push(rt);
	while(!q.empty()) {
		int u = q.front();
		dots[cnt].emplace_back(u, depcalc[u]);
		if(lim[u] - depcalc[u] >= 0) refer[u].emplace_back(cnt, lim[u] - depcalc[u]);
		q.pop();
		for(int i = G.head[u]; i; i = G.edge[i].nxt) if(viscalc[G.edge[i].to] != cnt && !vistc[G.edge[i].to]) {
			int v = G.edge[i].to;
			viscalc[v] = cnt, depcalc[v] = depcalc[u] + 1, q.push(v);
		}
	}
	// printf("[%d]: ", cnt); for(auto [u, d] : dots[cnt]) printf("(%d,%d) ", u, d); puts("");
}
void solve(int u) {
	calc(u);
	vistc[u] = true;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) if(!vistc[G.edge[i].to]) {
		int v = G.edge[i].to;
		getroot(v, u), allsize = sz[v], rootwt = INF, getroot(v, u), solve(root);
	}
}

LL dis[N], ans[N];
bool exist[N];
int cn;
void dijkstra(int t) {
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
	for(int i = 1; i <= cnt; i++) now[i] = 0;
	for(int i = 1; i <= n; i++) dis[i] = LLINF, exist[i] = true;
	exist[1] = false, dis[1] = 0, q.emplace(a[1].at(t), 1);
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		for(auto [i, d] : refer[u]) {
			while(now[i] < (int)dots[i].size() && dots[i][now[i]].second <= d) {
				cn++;
				if(exist[dots[i][now[i]].first]) {
					int v = dots[i][now[i]].first;
					// printf("%d -> %d (id=%d)\n", u, v, i);
					dis[v] = dis[u] + a[u].at(t), exist[v] = false;
					q.emplace(dis[v] + a[v].at(t), v);
				}
				now[i]++;
			}
		}
	}
	for(int i = 1; i <= n; i++) ans[i] = std::min(ans[i], dis[i]);
	fprintf(stderr, "cn = %d\n", cn);
}

int main() {
	freopen("brwal5.in", "r", stdin);
	freopen("brwal.out", "w", stdout);
	scanf("%d%d%lld", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%d%lld%lld", &lim[i], &a[i].b, &a[i].k);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); Go.add_edge(u, v), Go.add_edge(v, u); }
	dfs(1, 0);
	allsize = n, rootwt = INF, getroot(1, 0), solve(root);
	for(int i = 1; i <= n; i++) vistc[i] = false;
	for(auto [u, v] : extra) {
		G.add_edge(u, v), G.add_edge(v, u);
		calc(u);
	}
	for(int i = 1; i <= n; i++) ans[i] = LLINF;
	fprintf(stderr, "clock = %.3f\n", clock() / (double)CLOCKS_PER_SEC);
	dijkstra(0), dijkstra(K - 1);
	fprintf(stderr, "clock = %.3f\n", clock() / (double)CLOCKS_PER_SEC);
	for(int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
	return 0;
} /*
6 6 2
1 50 -40
1 2 100
2 1 100
2 4 100
3 1 100
1 1 100
1 2
2 3
3 4
4 2
2 5
6 1
*/