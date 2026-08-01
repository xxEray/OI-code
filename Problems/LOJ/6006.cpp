#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 1e3 + 5;
const int M = 20 + 5;
const int FLOW_N = N + M + 2; // vertice count
const int FLOW_M = N * M + N + M; // edge count
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
	int sum = 0;
	int src = n + m + 1, dst = n + m + 2;
	for(int i = 1; i <= m; i++) {
		int x; scanf("%d", &x);
		sum += x, dinic.add_edge(n + i, dst, x);
	}
	for(int i = 1; i <= n; i++) {
		dinic.add_edge(src, i, 1);
		int cnt, x; scanf("%d", &cnt);
		while(cnt--) scanf("%d", &x), dinic.add_edge(i, n + x, 1);
	}
	int ret = dinic.maxflow(n + m + 2, src, dst);
	if(ret < sum) { puts("No Solution!"); return 0; }
	for(int i = 1; i <= m; i++) {
		printf("%d: ", i);
		for(int j = dinic.head[i + n]; j; j = dinic.edge[j].nxt) if(dinic.edge[j].r) {
			int v = dinic.edge[j].to;
			if(v == dst) continue;
			printf("%d ", v);
		}
		puts("");
	}
	return 0;
}