#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 100 + 5;
const int FLOW_N = N * N + 2; // vertice count
const int FLOW_M = 6 * N * N; // edge count
const int INF = 0x3f3f3f3f;

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int a[N][N];
int n, m;

struct Dinic {
private:
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
public:
	Dinic() : ek(2) {}
	void add_edge(int u, int v, int c) { /* printf("%d -> %d (w=%d)\n", u, v, c); */ add_one_edge(u, v, c), add_one_edge(v, u, 0); }
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

int hash(int x, int y) { return (x - 1) * m + y; }

int main() {
	scanf("%d%d", &n, &m);
	int sum = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]), sum += a[i][j];
	int src = n * m + 1, dst = n * m + 2;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if((i ^ j) & 1) dinic.add_edge(hash(i, j), dst, a[i][j]);
		else {
			dinic.add_edge(src, hash(i, j), a[i][j]);
			for(int d = 0; d < 4; d++) {
				int oi = i + dir[d][0], oj = j + dir[d][1];
				if(oi < 1 || oi > n || oj < 1 || oj > m) continue;
				dinic.add_edge(hash(i, j), hash(oi, oj), INF);
			}
		}
	printf("%d\n", sum - dinic.mincut(n * m + 2, src, dst));
	return 0;
}