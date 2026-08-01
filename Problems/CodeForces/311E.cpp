#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;

const int N = 2e4 + 10;
const int M = 5e5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int sx[N]; LL a[N];
int n, m, s, t;
LL extra;

struct Edge { int to, nxt; LL r; } edge[M << 1];
int head[N], cur[N];
void add_single_edge(int u, int v, LL r) { static int k = 2; edge[k] = (Edge){v, head[u], r}, head[u] = k++; }
void add_edge(int u, int v, LL r) { add_single_edge(u, v, r), add_single_edge(v, u, 0); }

struct Dinic {
	int n, s, t;
	int dep[N];
	std::queue<int> q;
	bool bfs() {
		for(int i = 1; i <= n; i++) dep[i] = 0;
		dep[s] = 1, q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) if(!dep[edge[i].to] && edge[i].r) {
				int v = edge[i].to;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
		return dep[t];
	}
	LL dfs(int u, LL in) {
		if(u == t) return in;
		LL out = 0;
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	LL maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		LL ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, LLINF);
		}
		return ret;
	}
	inline LL mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); }
} dinic;

int main() {
	scanf("%d%d%lld", &n, &m, &extra);
	s = n + m + 2, t = n + m + 1;
	LL ans = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &sx[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) {
		int sex = sx[i]; LL w = a[i];
		if(sex) add_edge(i, t, w);
		else add_edge(s, i, w);
	}
	for(int i = 1; i <= m; i++) {
		int sex, c, fr; LL w;
		scanf("%d%lld%d", &sex, &w, &c);
		std::vector<int> dogs;
		while(c--) { int x; scanf("%d", &x); sex ? add_edge(x, n + i, LLINF) : add_edge(n + i, x, LLINF); }
		scanf("%d", &fr);
		ans += w;
		if(fr) w += extra;
		sex ? add_edge(n + i, t, w) : add_edge(s, n + i, w);
	}
	printf("%lld\n", ans - dinic.mincut(n + m + 2, s, t));
	return 0;
}