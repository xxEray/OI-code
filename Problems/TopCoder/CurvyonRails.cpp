#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

typedef long long LL;
const int N = 25 + 5;
const int FLOW_N = N * N * 3 + 2;
const int FLOW_M = N * N * N * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N][N];

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

int hsh(int x, int y) { return (x - 1) * m + y; }

class CurvyonRails {
public:
	int getmin(std::vector<std::string> field) {
		n = field.size(), m = field.front().size();
		int cnt = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = field[i - 1][j - 1], cnt += (a[i][j] != 'w');
		int src = n * m * 3 + 1, dst = n * m * 3 + 2;
		dinic.init(n * m * 3 + 2);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			if((i + j) & 1) {
				dinic.add_edge(src, hsh(i, j), a[i][j] == 'w' ? 0 : 2, 0);
				dinic.add_edge(hsh(i, j), hsh(i, j) + n * m, 1, 0), dinic.add_edge(hsh(i, j), hsh(i, j) + n * m, 1, a[i][j] == '.' ? 0 : 1);
				dinic.add_edge(hsh(i, j), hsh(i, j) + n * m * 2, 1, 0), dinic.add_edge(hsh(i, j), hsh(i, j) + n * m * 2, 1, a[i][j] == '.' ? 0 : 1);
			} else {
				dinic.add_edge(hsh(i, j), dst, a[i][j] == 'w' ? 0 : 2, 0);
				dinic.add_edge(hsh(i, j) + n * m, hsh(i, j), 1, 0), dinic.add_edge(hsh(i, j) + n * m, hsh(i, j), 1, a[i][j] == '.' ? 0 : 1);
				dinic.add_edge(hsh(i, j) + n * m * 2, hsh(i, j), 1, 0), dinic.add_edge(hsh(i, j) + n * m * 2, hsh(i, j), 1, a[i][j] == '.' ? 0 : 1);
			}
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if((i + j) & 1) {
			if(i > 1) dinic.add_edge(hsh(i, j) + n * m, hsh(i - 1, j) + n * m, 1, 0);
			if(i < n) dinic.add_edge(hsh(i, j) + n * m, hsh(i + 1, j) + n * m, 1, 0);
			if(j > 1) dinic.add_edge(hsh(i, j) + n * m * 2, hsh(i, j - 1) + n * m * 2, 1, 0);
			if(j < m) dinic.add_edge(hsh(i, j) + n * m * 2, hsh(i, j + 1) + n * m * 2, 1, 0);
		}
		auto p = dinic.mincost(src, dst);
		if(p.first < cnt) return -1;
		else return p.second;
	}
};

/* int main() {
	CurvyonRails T;
	printf("%d\n", T.getmin(...));
	return 0;
} */