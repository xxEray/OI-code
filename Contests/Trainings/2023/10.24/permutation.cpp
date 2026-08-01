#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = 5 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int a[N], b[N];

struct DSU {
	int fa[N];
	void init() { for(int i = 1; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
} dsua, dsub;

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

int wa[N], wb[N];
std::map<std::pair<int, int>, int> mp1, mp2;

int main() {
#ifndef DEBUG
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	dsua.init(), dsub.init();
	for(int i = 1; i <= n; i++) dsua.merge(i, a[i]), dsub.merge(i, b[i]);
	int base = 0;
	for(int i = 1; i <= n; i++) base += (a[i] == i && b[i] == i);
	int src = 2 * n + 1, dst = 2 * n + 2;
	dinic.init(2 * n + 2);
	for(int i = 1; i <= n; i++) mp1[{dsua.find(i), dsub.find(i)}] += (a[i] != i && b[i] != i && a[i] != b[i]);
	for(int i = 1; i <= n; i++) mp2[{dsua.find(i), dsub.find(i)}] += (a[i] != i && b[i] != i && a[i] == b[i]);
	for(int i = 1; i <= n; i++) wa[dsua.find(i)] += (a[i] != i && b[i] == i);
	for(int i = 1; i <= n; i++) wb[dsub.find(i)] += (a[i] == i && b[i] != i);
	for(int i = 1; i <= n; i++) dinic.add_edge(src, i, wa[i]);
	for(int i = 1; i <= n; i++) dinic.add_edge(i + n, dst, wb[i]);
	for(const auto &[p, v] : mp1) dinic.add_edge(p.second + n, p.first, v);
	for(const auto &[p, v] : mp2) dinic.add_edge(p.first, p.second + n, v), dinic.add_edge(p.second + n, p.first, v);
	printf("%lld\n", base + dinic.mincut(src, dst));
	return 0;
} /*
6
2 3 1 5 4 6
1 2 3 4 5 6
*/