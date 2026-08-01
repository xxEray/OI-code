#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 50 + 5;
const int FLOW_N = N * N * 2 + 2;
const int FLOW_M = N * N * 6;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N][N];

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

int hsh(int x, int y) { return (x - 1) * m + y; }

class BoardPainting {
public:
	int minimalSteps(std::vector<std::string> target) {
		n = target.size(), m = target.front().size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = target[i - 1][j - 1] == '#';
		int cnt = 0, tot = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cnt += a[i][j];
		int src = n * m * 2 + 1, dst = n * m * 2 + 2;
		dinic.init(n * m * 2 + 2);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
			if(i < n && j < m && a[i][j] && a[i + 1][j] && a[i][j + 1]) dinic.add_edge(hsh(i, j), hsh(i, j) + n * m, LLINF);
			if(i > 1 && j < m && a[i][j] && a[i - 1][j] && a[i][j + 1]) dinic.add_edge(hsh(i, j), hsh(i - 1, j) + n * m, LLINF);
			if(i < n && j > 1 && a[i][j] && a[i + 1][j] && a[i][j - 1]) dinic.add_edge(hsh(i, j - 1), hsh(i, j) + n * m, LLINF);
			if(i > 1 && j > 1 && a[i][j] && a[i - 1][j] && a[i][j - 1]) dinic.add_edge(hsh(i, j - 1), hsh(i - 1, j) + n * m, LLINF);
			if(j < m && a[i][j] && a[i][j + 1]) tot++, dinic.add_edge(src, hsh(i, j), 1);
			if(i < n && a[i][j] && a[i + 1][j]) tot++, dinic.add_edge(hsh(i, j) + n * m, dst, 1);
		}
		return cnt - (tot - dinic.mincut(src, dst));
	}
};