#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;
const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = M + 2 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;

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

std::pair<int, int> out[N];

bool vis[N];
void dfs(int u) {
	// printf("%d\n", u);
	for(int i = dinic.head[u]; i; i = dinic.edge[i].nxt) {
		int v = dinic.edge[i].to;
		if(n + 1 <= v && v <= 2 * n - 1 && !vis[v - n]) {
			vis[v - n] = true;
			for(int j = dinic.head[v]; j; j = dinic.edge[j].nxt)
				if(1 <= dinic.edge[j].to && dinic.edge[j].to <= n && dinic.edge[j].r == 1)
					{ out[v - n] = {u, dinic.edge[j].to}, dfs(dinic.edge[j].to); break; }
		}
	}
}

int main() {
	scanf("%d", &n);
	int src = 2 * n, dst = 2 * n + 1;
	dinic.init(2 * n + 1);
	for(int i = 1; i <= n; i++) dinic.add_edge(src, i, 1);
	for(int i = 1; i < n; i++) dinic.add_edge(i + n, dst, 1);
	for(int i = 1; i < n; i++) {
		int c, x; scanf("%d", &c);
		while(c--) scanf("%d", &x), dinic.add_edge(x, i + n, 1);
	}
	if(dinic.maxflow(src, dst) < n - 1) { puts("-1"); return 0; }
	// for(int i = 1; i <= 2 * n + 1; i++) for(int j = dinic.head[i]; j; j = dinic.edge[j].nxt)
	// 	if(!(j & 1) && dinic.edge[j ^ 1].r == 1) printf("%d -> %d\n", i, dinic.edge[j].to);
	for(int i = dinic.head[src]; i; i = dinic.edge[i].nxt) if(dinic.edge[i ^ 1].r == 0) { dfs(dinic.edge[i].to); break; }
	for(int i = 1; i < n; i++) if(out[i].first == 0) { puts("-1"); return 0; }
	for(int i = 1; i < n; i++) printf("%d %d\n", out[i].first, out[i].second);
	return 0;
}