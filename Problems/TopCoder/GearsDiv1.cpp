#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

typedef long long LL;

const int N = 50 + 5;
const int FLOW_N = N + 2;
const int FLOW_M = N * N + N * 2;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int a[N];
bool e[N][N];

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

LL ans = LLINF;
void solve(char c1, char c2) {
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 1; i <= n; i++) if(a[i] == c1) dinic.add_edge(src, i, 1);
	for(int i = 1; i <= n; i++) if(a[i] == c2) dinic.add_edge(i, dst, 1);
	for(int i = 1; i <= n; i++) if(a[i] == c1)
		for(int j = 1; j <= n; j++) if(a[j] == c2)
			if(e[i][j]) dinic.add_edge(i, j, LLINF);
	ans = std::min(ans, dinic.mincut(src, dst));
}

class GearsDiv1 {
public:
	int getmin(std::string color, std::vector<std::string> graph) {
		n = color.size();
		for(int i = 1; i <= n; i++) a[i] = color[i - 1];
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = (graph[i - 1][j - 1] == 'Y');
		solve('R', 'G'), solve('G', 'B'), solve('R', 'B');
		return ans;
	}
};