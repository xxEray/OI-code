#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;
const int N = 1e5 + 5;
const int FLOW_N = N + 2;
const int FLOW_M = N * 4;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int a[N], b[N];

struct Dinic {
	struct Edge { int to, nxt; LL r, w; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	LL dep[FLOW_N];
	bool inq[FLOW_N];
	std::queue<int> q;
	LL flow, cost;
	void add_one_edge(int u, int v, LL c, LL w) { edge[ek] = (Edge){v, head[u], c, w}, head[u] = ek++; }
	bool spfa() {
		for(int i = 1; i <= n; i++) dep[i] = LLINF, inq[i] = false;
		dep[s] = 1, q.push(s), inq[s] = true;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for(int i = head[u]; i; i = edge[i].nxt) if(dep[edge[i].to] > dep[u] + edge[i].w && edge[i].r) {
				int v = edge[i].to;
				dep[v] = dep[u] + edge[i].w;
				if(!inq[v]) q.push(v), inq[v] = true;
			}
		}
		return dep[t] != LLINF;
	}
	LL dfs(int u, LL in) {
		if(u == t) return in;
		inq[u] = true;
		LL out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(!inq[edge[i].to] && dep[edge[i].to] == dep[u] + edge[i].w && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			cost += ret * edge[i].w;
			if(!in) return out;
		}
		if(!out) dep[u] = 0;
		inq[u] = false;
		return out;
	}
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, LL c, LL w) { add_one_edge(u, v, c, w), add_one_edge(v, u, 0, -w); }
	std::pair<LL, LL> mincost(int s_, int t_) {
		s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i], inq[i] = false;
			flow += dfs(s, LLINF);
		}
		return {flow, cost};
	}
} dinic;

int main() {
	scanf("%d", &n);
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); dinic.add_edge(i, dst, x, 0); }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) dinic.add_edge(src, i, a[i], b[i]);
	for(int i = 1; i < n; i++) { int x; scanf("%d", &x); dinic.add_edge(i, i + 1, LLINF, x); }
	for(int i = 1; i < n; i++) { int x; scanf("%d", &x); dinic.add_edge(i + 1, i, LLINF, x); }
	printf("%lld\n", dinic.mincost(src, dst).second);
	for(int i = 2; i < dinic.ek; i += 2) printf("%d -> %d (c=%lld,f=%lld)\n", dinic.edge[i ^ 1].to, dinic.edge[i].to, dinic.edge[i].w, dinic.edge[i ^ 1].r);
	return 0;
}