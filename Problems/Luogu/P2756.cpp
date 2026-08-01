// the same as LOJ6000
#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 100 + 5;

const int FLOW_N = 2 * N + 2;
const int FLOW_M = 4 * N + N * N;
const int INF = 0x3f3f3f3f;

int n, m;

struct Dinic {
	struct Edge { int to, nxt; int r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
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
	int dfs(int u, int in) {
		if(u == t) return in;
		int out = 0;
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	Dinic() : ek(2) {}
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	inline int mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); } // mincut = maxflow
} dinic;

int main() {
	scanf("%d%d", &m, &n);
	int s = n * 2 + 1, t = n * 2 + 2;
	int x, y;
	while(scanf("%d%d", &x, &y) == 2 && x != -1 && y != -1) dinic.add_edge(n + x, y, 1);
	for(int i = 1; i <= m; i++) dinic.add_edge(s, i, 1), dinic.add_edge(i, n + i, 1);
	for(int i = m + 1; i <= n; i++) dinic.add_edge(i, n + i, 1), dinic.add_edge(n + i, t, 1);
	printf("%d\n", dinic.maxflow(n * 2 + 2, s, t));
	for(int i = 1; i <= m; i++) for(int k = dinic.head[n + i]; k; k = dinic.edge[k].nxt) {
		int j = dinic.edge[k].to;
		if(m + 1 <= j && j <= n && dinic.edge[k ^ 1].r) printf("%d %d\n", i, j);
	}
	return 0;
}