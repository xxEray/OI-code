#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 2000 + 5;
const int FLOW_N = N * 2 + 2; // vertice count
const int FLOW_M = N * 6; // edge count
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N];
int n, m;
LL buy_cost, fast_cost, slow_cost, fast_time, slow_time;

struct Dinic {
private:
	struct Edge { int to, nxt; LL r, w; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	LL dep[FLOW_N];
	bool inq[FLOW_N];
	std::queue<int> q;
	LL flow, cost;
	void add_one_edge(int u, int v, LL c, LL w) { edge[ek] = (Edge){v, head[u], c, w}, head[u] = ek++; }
	bool spfa() {
		for(int i = 1; i <= n; i++) dep[i] = LLINF;
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
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(!inq[edge[i].to] && dep[edge[i].to] == dep[u] + edge[i].w && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			cost += ret * edge[i].w;
		}
		if(!out) dep[u] = 0;
		inq[u] = false;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void add_edge(int u, int v, LL c, LL w) { /* printf("%d %d \"c=%lld, w=%lld\"\n", u, v, c, w); */ add_one_edge(u, v, c, w), add_one_edge(v, u, 0, -w); }
	std::pair<LL, LL> mincost(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			flow += dfs(s, LLINF);
		}
		return {flow, cost};
	}
} dinic;

int main() {
	scanf("%d", &n);
	scanf("%lld%lld%lld%lld%lld", &buy_cost, &fast_time, &fast_cost, &slow_time, &slow_cost);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	int src = n * 2 + 1, dst = n * 2 + 2;
	for(int i = 1; i <= n; i++) {
		dinic.add_edge(src, i, LLINF, buy_cost);
		dinic.add_edge(i, dst, a[i], 0);
		dinic.add_edge(src, i + n, a[i], 0);
		if(i + 1 <= n) dinic.add_edge(i + n, i + 1 + n, LLINF, 0);
		if(i + fast_time <= n) dinic.add_edge(i + n, i + fast_time, LLINF, fast_cost);
		if(i + slow_time <= n) dinic.add_edge(i + n, i + slow_time, LLINF, slow_cost);
	}
	printf("%lld\n", dinic.mincost(n * 2 + 2, src, dst).second);
	return 0;
}