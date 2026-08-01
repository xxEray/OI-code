#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

typedef long long LL;
const int N = 20 + 5;
const int FLOW_N = N * N * 2 + 2;
const int FLOW_M = N * N * 6;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N][N], b[N][N];

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

int trans(char c) {
	if('0' <= c && c <= '9') return c - '0';
	else if('a' <= c && c <= 'z') return c - 'a' + 10;
	else if('A' <= c && c <= 'Z') return c - 'A' + 36;
	else return assert(false), 0;
}

int hsh(int x, int y) { return (x - 1) * m + y; }

class SurroundingGame {
public:
	int maxScore(std::vector<std::string> cost, std::vector<std::string> benefit) {
		n = cost.size(), m = cost.front().size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = trans(cost[i - 1][j - 1]), b[i][j] = trans(benefit[i - 1][j - 1]);
		int src = n * m * 2 + 1, dst = n * m * 2 + 2;
		dinic.init(n * m * 2 + 2);
		LL sum = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) sum += b[i][j];
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			if((i + j) & 1) {
				dinic.add_edge(src, hsh(i, j), a[i][j]);
				dinic.add_edge(hsh(i, j), hsh(i, j) + n * m, b[i][j]);
				if(i > 1) dinic.add_edge(hsh(i, j) + n * m, hsh(i - 1, j), LLINF);
				if(i < n) dinic.add_edge(hsh(i, j) + n * m, hsh(i + 1, j), LLINF);
				if(j > 1) dinic.add_edge(hsh(i, j) + n * m, hsh(i, j - 1), LLINF);
				if(j < m) dinic.add_edge(hsh(i, j) + n * m, hsh(i, j + 1), LLINF);
			} else {
				dinic.add_edge(hsh(i, j), dst, a[i][j]);
				dinic.add_edge(hsh(i, j) + n * m, hsh(i, j), b[i][j]);
				if(i > 1) dinic.add_edge(hsh(i - 1, j), hsh(i, j) + n * m, LLINF);
				if(i < n) dinic.add_edge(hsh(i + 1, j), hsh(i, j) + n * m, LLINF);
				if(j > 1) dinic.add_edge(hsh(i, j - 1), hsh(i, j) + n * m, LLINF);
				if(j < m) dinic.add_edge(hsh(i, j + 1), hsh(i, j) + n * m, LLINF);
			}
		return sum - dinic.mincut(src, dst);
	}
};