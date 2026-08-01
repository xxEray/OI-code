#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;
const int N = 5e3 + 5;
const int M = 5e4 + 5;
const int FLOW_N = N + 2;
const int FLOW_M = 2 * M + 2 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
LL w[N];
int e[M][3];

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
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			if(!in) return out;
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
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &w[i]), w[i] *= 2;
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]), w[e[i][0]] -= e[i][2], w[e[i][1]] -= e[i][2];
	LL mn = LLINF;
	for(int i = 1; i <= n; i++) mn = std::min(mn, w[i]);
	for(int i = 1; i <= n; i++) dinic.add_edge(src, i, mn), dinic.add_edge(i, dst, mn + w[i]);
	for(int i = 1; i <= m; i++) dinic.add_edge(e[i][0], e[i][1], e[i][2]), dinic.add_edge(e[i][1], e[i][0], e[i][2]);
	printf("%lld\n", -(dinic.maxflow(src, dst) - n * mn) / 2);
	return 0;
}