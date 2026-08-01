#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;
const int N = 200 + 5;
const int FLOW_N = N + 2;
const int FLOW_M = N * N + 3 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;
const LL LARGE = 1e17;

int n, m;
LL a[N];

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
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, LL c, LL w) { add_one_edge(u, v, c, w), add_one_edge(v, u, 0, -w); }
	std::pair<LL, LL> mincost(int s_, int t_) {
		s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			flow += dfs(s, LLINF);
		}
		return {flow, cost};
	}
} dinic;

std::vector<int> vct;
bool check() {
	for(int e : vct) if(dinic.edge[e].r) return false;
	return true;
}

int main() {
#ifndef DEBUG
	freopen("endemic.in", "r", stdin);
	freopen("endemic.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	n++;
	for(int i = n; i >= 1; i--) a[i] -= a[i - 1];
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 2; i <= n - 1; i++) {
		if(a[i] < 0) vct.push_back(dinic.ek), dinic.add_edge(i, dst, -a[i], 0);
		else if(a[i] > 0) dinic.add_edge(src, i, a[i], 0);
	}
	dinic.add_edge(src, 1, 2 * LARGE, 0), dinic.add_edge(src, n, 2 * LARGE, 0);
	dinic.add_edge(1, dst, LARGE, 0), dinic.add_edge(n, dst, LARGE, 0);
	while(m--) {
		char s[2]; int l; LL w;
		scanf("%s%d%lld", s, &l, &w);
		if(s[0] == '+') for(int i = 1; i + l <= n; i++) dinic.add_edge(i + l, i, LARGE, w);
		else for(int i = 1; i + l <= n; i++) dinic.add_edge(i, i + l, LARGE, w);
	}
	auto ans = dinic.mincost(src, dst);
	if(check()) printf("%lld\n", ans.second);
	else puts("-1");
	return 0;
}