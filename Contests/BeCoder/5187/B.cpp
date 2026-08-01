#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e4 + 5;
const int FLOW_N = 4 * N;
const int FLOW_M = 4 * N * 20;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
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

int tin[N];
std::vector<int> factor[N];

int main() {
	for(int i = 1; i <= 50000; i++) for(int j = i + i; j <= 50000; j += i) factor[j].emplace_back(i);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int src = 4 * n + 1, dst = 4 * n + 2;
		dinic.init(4 * n + 2);
		for(int i = 1; i <= 2 * n; i++) dinic.add_edge(src, i, 1), dinic.add_edge(i + 2 * n, dst, 1);
		for(int i = 1; i <= n; i++) dinic.add_edge(i, i + 3 * n, 1); // , printf("%d %d\n", i, i + n);
		for(int i = 1; i <= n; i++) tin[a[i]] = i;
		for(int i = 1; i <= n; i++)
			for(int y : factor[a[i]]) if(tin[y]) {
				int j = tin[y];
				// printf("%d %d\n%d %d\n%d %d\n", i, j, i, j + n, i + n, j + n);
				dinic.add_edge(i, j + 2 * n, 1), dinic.add_edge(i, j + 3 * n, 1), dinic.add_edge(i + n, j + 3 * n, 1);
			}
		int flow = dinic.maxflow(src, dst);
		printf("%d\n", n - (2 * n - flow));
		for(int i = 1; i <= n; i++) tin[a[i]] = 0;
	}
	return 0;
} /*
1
4
30 2 3 5
*/