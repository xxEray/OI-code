#include <cstdio>
#include <algorithm>
#include <queue>
#include <cassert>

const int N = 200 + 5;
const int M = 6000 + 5;
const int INF = 0x3f3f3f3f;
const int FLOW_N = N * 2 + 2;
const int FLOW_M = N * 2 + M;

int n, m;

struct Dinic {
	struct Edge { int to, nxt, r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int dep[FLOW_N];
	int n, s, t;
	Dinic() : ek(2) {}
	void add_one_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }
	void add_edge(int u, int v, int w) { add_one_edge(u, v, w), add_one_edge(v, u, 0); }
	bool bfs() {
		std::queue<int> q;
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
	int dfs(int u, int in) {
		if(u == t) return in;
		int out = 0;
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[edge[i].to] == dep[u] + 1 && edge[i].r) {
			int v = edge[i].to;
			int w = dfs(v, std::min(in, edge[i].r));
			edge[i].r -= w, edge[i ^ 1].r += w;
			in -= w, out += w;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	int maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	int mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); }
} dinic;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[y] = x : 0; }

int to[N];

int main() {
	scanf("%d%d", &n, &m);
	int s = n * 2 + 1, t = n * 2 + 2;
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		dinic.add_edge(u, v + n, 1);
	}
	for(int i = 1; i <= n; i++) dinic.add_edge(s, i, 1), dinic.add_edge(i + n, t, 1);
	int ans = n - dinic.maxflow(n * 2 + 2, s, t);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) for(int j = dinic.head[i]; j; j = dinic.edge[j].nxt) if(dinic.edge[j ^ 1].r) {
		int v = dinic.edge[j].to - n;
		if(v + n == s) continue;
		assert(1 <= v && v <= n);
		to[i] = v, merge(i, v);
	}
	for(int i = 1; i <= n; i++) if(find(i) == i) {
		int j = i;
		printf("%d ", j);
		while(to[j]) j = to[j], printf("%d ", j);
		puts("");
	}
	printf("%d\n", ans);
	return 0;
}