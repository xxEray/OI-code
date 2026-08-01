#include <cstdio>
#include <algorithm>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 1e4 + 5;
const int FLOW_N = 2 * N + 7; // vertice count
const int FLOW_M = 3 * N + 5; // edge count
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, Q;
struct Node { int u, t; } a[N];
bool operator<(Node x, Node y) { return x.u < y.u; }

struct Dinic {
private:
	struct Edge { int to, nxt; LL r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, LL c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
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
public:
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, LL c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	LL maxflow(int s_, int t_) {
		s = s_, t = t_;
		LL ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, LLINF);
		}
		return ret;
	}
	inline LL mincut(int s_, int t_) { return maxflow(s_, t_); } // mincut = maxflow
} dinic;

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &a[i].u, &a[i].t);
	std::sort(a + 1, a + Q + 1);
	Q++;
	a[Q].u = m, a[Q].t = n;
	dinic.init(Q + m + 7);
	int src = Q + m + 6, dst = Q + m + 7;
	for(int i = 1; i <= Q; i++) if(a[i].t < a[i - 1].t) { puts("unfair"); return 0; }
	for(int i = 1; i <= Q; i++) dinic.add_edge(src, m + i, a[i].t - a[i - 1].t);
	for(int i = 1; i <= Q; i++) for(int j = a[i - 1].u + 1; j <= a[i].u; j++) dinic.add_edge(m + i, j, 1);
	for(int i = 1; i <= m; i++) dinic.add_edge(i, Q + m + (i % 5) + 1, 1);
	for(int i = 1; i <= 5; i++) dinic.add_edge(Q + m + i, dst, n / 5);
	puts(dinic.maxflow(src, dst) == n ? "fair" : "unfair");
	return 0;
}