#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;
const int N = 250 + 6;
const int M = 26 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = N * N + 2 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N];

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
public:
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

int bit(int x) {
	int d = 0;
	while(x) x /= 10, d++;
	return d;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int src = n + 1, src2 = n + 2, dst = n + 3;
	dinic.init(n + 3);
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++)
		if(a[i] == a[j]) dinic.add_edge(i, j, 1, 0);
		else dinic.add_edge(i, j, 1, bit(a[j]));
	dinic.add_edge(src, src2, m, 0);
	for(int i = 1; i <= n; i++) dinic.add_edge(src2, i, 1, bit(a[i])), dinic.add_edge(i, dst, 1, 0);
	auto p = dinic.mincost(src, dst);
	printf("%lld\n", p.second);
	return 0;
}