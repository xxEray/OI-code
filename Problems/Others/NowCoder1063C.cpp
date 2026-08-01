#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 100 + 5;
const int FLOW_N = N * N + 2;
const int FLOW_M = N * N * 9;
const int INF = 0x3f3f3f3f;

const int dir[8][2] = {{1, 2}, {2, 1}, {-1, -2}, {-2, -1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}};

int n, m, K;
bool a[N][N];

int hash(int i, int j) { return (i - 1) * m + j; }

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
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = true;
	while(K--) { int x, y; scanf("%d%d", &x, &y); a[x][y] = false; }
	int src = n * m + 1, dst = n * m + 2;
	int sum = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(a[i][j]) {
		sum++;
		if((i + j) & 1) dinic.add_edge(hash(i, j), dst, 1);
		else dinic.add_edge(src, hash(i, j), 1);
		for(int d = 0; d < 8; d++) {
			int dx = i + dir[d][0], dy = j + dir[d][1];
			if(dx < 1 || dx > n || dy < 1 || dy > m || !a[dx][dy]) continue;
			if((i + j) & 1) dinic.add_edge(hash(dx, dy), hash(i, j), 1);
			else dinic.add_edge(hash(i, j), hash(dx, dy), 1);
		}
	}
	printf("%d\n", sum - dinic.maxflow(n * m + 2, src, dst));
	return 0;
}