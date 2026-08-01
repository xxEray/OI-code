#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;
const int N = 50 + 5;
const int M = 1000 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = 2 * M + 3 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N];

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

class RatingProgressAward {
public:
	int maximalProgress(std::vector<int> change, std::vector<int> eu, std::vector<int> ev) {
		n = change.size(), m = eu.size();
		LL sum = 0;
		for(int i = 1; i <= n; i++) a[i] = change[i - 1], sum += (a[i] > 0 ? a[i] : 0);
		int src = 2 * n + 1, dst = 2 * n + 2;
		dinic.init(2 * n + 2);
		for(int i = 0; i < m; i++) {
			dinic.add_edge(ev[i] + 1, eu[i] + 1, LLINF);
			dinic.add_edge(ev[i] + n + 1, eu[i] + n + 1, LLINF);
		}
		for(int i = 1; i <= n; i++) {
			dinic.add_edge(src, i, a[i] > 0 ? a[i] : 0);
			dinic.add_edge(i, i + n, a[i] < 0 ? -a[i] : 0);
			dinic.add_edge(i + n, dst, a[i] > 0 ? a[i] : 0);
		}
		return sum - dinic.mincut(src, dst);
	}
};