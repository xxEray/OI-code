#include <cstdio>
#include <algorithm>
#include <queue>

const int R = 100 + 5;
const int N = R * 4 + 2;
const int M = R * R * 2 + 3 * R;
const int INF = 0x3f3f3f3f;

int n, m, Q;

struct Dinic {
private:
	struct Edge { int to, nxt; int r; } edge[M << 1];
	int head[N], cur[N], ek;
	int n, s, t;
	int dep[N];
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
public:
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

int hash(int r, int c) { return Q + (r - 1) * m + c; }

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	int s = 2 * Q + n + m + 1, t = 2 * Q + n + m + 2;
	for(int i = 1; i <= Q; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		dinic.add_edge(i, Q + i, 1);
		for(int j = x1; j <= x2; j++) dinic.add_edge(2 * Q + j, i, 1);
		for(int j = y1; j <= y2; j++) dinic.add_edge(Q + i, 2 * Q + n + j, 1);
	}
	for(int i = 1; i <= n; i++) dinic.add_edge(s, 2 * Q + i, 1);
	for(int i = 1; i <= m; i++) dinic.add_edge(2 * Q + n + i, t, 1);
	printf("%d\n", dinic.maxflow(2 * Q + n + m + 2, s, t));
	return 0;
}