#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;
const int N = 1e3 + 5;
const int FLOW_N = 1e3 + 5;
const int FLOW_M = 1e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, src, dst;

struct Dinic {
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

bool fs[N], ft[N];

void dfss(int u) {
	if(fs[u]) return;
	fs[u] = true;
	for(int i = dinic.head[u]; i; i = dinic.edge[i].nxt) if(dinic.edge[i ^ 1].r == 0) dfss(dinic.edge[i].to);
}
void dfst(int u) {
	if(ft[u]) return;
	ft[u] = true;
	for(int i = dinic.head[u]; i; i = dinic.edge[i].nxt) if(dinic.edge[i].r == 0) dfst(dinic.edge[i].to);
}

int main() {
	while(scanf("%d%d%d%d", &n, &m, &src, &dst) == 4 && (n | m | src | dst)) {
		dinic.init(n);
		for(int i = 1; i <= n; i++) fs[i] = ft[i] = false;
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); dinic.add_edge(u, v, 1); }
		int ans = dinic.maxflow(src, dst);
		dfss(src), dfst(dst);
		// for(int i = 1; i <= n; i++) printf("%d: %d %d\n", i, fs[i], ft[i]);
		int tot = 0;
		for(int i = 2; i <= 2 * m; i += 2) {
			int u = dinic.edge[i ^ 1].to, v = dinic.edge[i].to;
			if(dinic.edge[i].r && fs[v] && ft[u]) tot++;
		}
		printf("%d %d\n", ans + (bool)tot, tot);
	}
	return 0;
}