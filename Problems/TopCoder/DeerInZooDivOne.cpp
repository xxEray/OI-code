#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;
const int N = 50 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = N * N + 2 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int head[N];
struct Edge { int to, nxt; } edge[N << 1];
void add_edge(int u, int v) { static int k = 2; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int cut;

int dfn[N], sz[N];
void dfs(int u, int fa) {
	static int time_stamp = 0;
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
bool ancestor(int x, int y) { return dfn[x] <= dfn[y] && dfn[y] <= dfn[x] + sz[x] - 1; }

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
		dep[s] = 0, q.push(s), inq[s] = true;
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
		if(!out) dep[u] = -LLINF;
		inq[u] = false;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void init(int n_) { n = n_; ek = 2; for(int i = 1; i <= n; i++) head[i] = 0; }
	void add_edge(int u, int v, LL c, LL w) { add_one_edge(u, v, c, -w), add_one_edge(v, u, 0, w); }
	std::pair<LL, LL> maxcost(int s_, int t_) {
		s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i], inq[i] = false;
			flow += dfs(s, LLINF);
		}
		return {flow, -cost};
	}
};

int f2[N << 1][N << 1];
int dfs2(int e1, int e2) {
	if(f2[e1][e2] != -1) return f2[e1][e2];
	int u1 = edge[e1].to, u2 = edge[e2].to;
	std::vector<int> vct1, vct2;
	for(int i = head[u1]; i; i = edge[i].nxt) if(i != (e1 ^ 1) && i != cut && i != (cut ^ 1)) vct1.push_back(i);
	for(int i = head[u2]; i; i = edge[i].nxt) if(i != (e2 ^ 1) && i != cut && i != (cut ^ 1)) vct2.push_back(i);
	int cnt1 = vct1.size(), cnt2 = vct2.size();
	int src = cnt1 + cnt2 + 1, dst = cnt1 + cnt2 + 2;
	Dinic dinic;
	dinic.init(cnt1 + cnt2 + 2);
	for(int i = 1; i <= cnt1; i++) dinic.add_edge(src, i, 1, 0);
	for(int i = 1; i <= cnt2; i++) dinic.add_edge(i + cnt1, dst, 1, 0);
	for(int i = 1; i <= cnt1; i++) for(int j = 1; j <= cnt2; j++) dinic.add_edge(i, j + cnt1, 1, dfs2(vct1[i - 1], vct2[j - 1]));
	return f2[e1][e2] = dinic.maxcost(src, dst).second + 1;
}
int f1[N][N];
int dfs1(int u1, int u2) {
	if(f1[u1][u2] != -1) return f1[u1][u2];
	std::vector<int> vct1, vct2;
	for(int i = head[u1]; i; i = edge[i].nxt) if(i != cut && i != (cut ^ 1)) vct1.push_back(i);
	for(int i = head[u2]; i; i = edge[i].nxt) if(i != cut && i != (cut ^ 1)) vct2.push_back(i);
	int cnt1 = vct1.size(), cnt2 = vct2.size();
	int src = cnt1 + cnt2 + 1, dst = cnt1 + cnt2 + 2;
	Dinic dinic;
	dinic.init(cnt1 + cnt2 + 2);
	for(int i = 1; i <= cnt1; i++) dinic.add_edge(src, i, 1, 0);
	for(int i = 1; i <= cnt2; i++) dinic.add_edge(i + cnt1, dst, 1, 0);
	for(int i = 1; i <= cnt1; i++) for(int j = 1; j <= cnt2; j++) dinic.add_edge(i, j + cnt1, 1, dfs2(vct1[i - 1], vct2[j - 1]));
	return f1[u1][u2] = dinic.maxcost(src, dst).second + 1;
}

class DeerInZooDivOne {
public:
	int getmax(std::vector<int> a, std::vector<int> b) {
		n = a.size() + 1;
		for(int i = 1; i < n; i++) add_edge(a[i - 1] + 1, b[i - 1] + 1), add_edge(b[i - 1] + 1, a[i - 1] + 1);
		dfs(1, 0);
		int ans = 0;
		for(cut = 2; cut <= 2 * (n - 1); cut += 2) {
			for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f1[i][j] = -1;
			for(int i = 2; i <= 2 * n - 1; i++) for(int j = 2; j <= 2 * n - 1; j++) f2[i][j] = -1;
			int u = a[cut / 2 - 1] + 1, v = b[cut / 2 - 1] + 1;
			if(ancestor(u, v)) std::swap(u, v);
			for(int i = 1; i <= n; i++) if(ancestor(u, i))
				for(int j = 1; j <= n; j++) if(!ancestor(u, j))
					ans = std::max(ans, dfs1(i, j));
		}
		return ans;
	}
};

// int main() {
// 	DeerInZooDivOne T;
// 	printf("%d\n", T.getmax({28, 19, 5, 35, 5, 31, 42, 28, 33, 3, 9, 38, 20, 7, 1, 11, 26, 12, 17, 3, 46, 48, 8, 19, 21, 41, 16, 32, 43, 45, 42, 26, 24, 36, 37, 33, 7, 11, 29, 39, 24, 44, 22, 40, 18, 48, 1, 13, 15}, {27, 18, 4, 34, 6, 30, 43, 29, 32, 2, 10, 37, 21, 6, 0, 12, 27, 13, 16, 4, 47, 49, 9, 20, 22, 40, 15, 31, 44, 46, 41, 25, 23, 35, 36, 34, 8, 10, 30, 38, 25, 45, 23, 39, 17, 47, 2, 14, 14}));
// 	return 0;
// }