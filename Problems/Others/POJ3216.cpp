#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 20 + 5;
const int M = 200 + 5;
const int FLOW_N = M * 2 + 2;
const int FLOW_M = M * M + 2 * M;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL dis[N][N];
int p[M], t[M], d[M];

struct Dinic {
private:
	struct Edge { int to, nxt; int r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, int c) { edge[ek].to = v, edge[ek].nxt = head[u], edge[ek].r = c, head[u] = ek++; }
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
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n_; i++) head[i] = 0; }
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int maxflow(int s_, int t_) {
		s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	inline int mincut(int n_, int s_, int t_) { return maxflow(s_, t_); } // mincut = maxflow
} dinic;

int main() {
	while(scanf("%d%d", &n, &m) == 2 && (n | m)) {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
			scanf("%lld", &dis[i][j]);
			if(dis[i][j] == -1) dis[i][j] = LLINF;
		}
		for(int i = 1; i <= m; i++) scanf("%d%d%d", &p[i], &t[i], &d[i]);
		for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
			dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
		dinic.init(2 * m + 2);
		int src = 2 * m + 1, dst = 2 * m + 2;
		for(int i = 1; i <= m; i++) dinic.add_edge(src, i, 1), dinic.add_edge(i + m, dst, 1);
		for(int i = 1; i <= m; i++) for(int j = 1; j <= m; j++)
			if(i != j && t[i] + d[i] + dis[p[i]][p[j]] <= t[j]) dinic.add_edge(i, j + m, 1);
		printf("%d\n", m - dinic.maxflow(src, dst));
	}
	return 0;
}