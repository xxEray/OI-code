#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;

const int N = 500 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = N * N + 2 * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int a[N][N];

struct Dinic {
public:
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
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
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

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int id[N], ld[N], cnt[N][N], pos[N][N], tot[N], bel[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
	dinic.init(2 * m + 2);
	int src = 2 * m + 1, dst = 2 * m + 2;
	for(int i = 1; i <= m; i++) if(!bel[i])
		for(int j = 1; j <= m; j++) if(!bel[j] && i != j) {
			bool flag = true;
			for(int k = 1; k <= n; k++) flag &= a[k][i] == a[k][j];
			if(!flag) continue;
			bel[j] = i;
		}
	for(int i = 1; i <= m; i++) if(!bel[i]) {
		dinic.add_edge(src, i, 1);
		dinic.add_edge(i + m, dst, 1);
	}
	for(int i = 1; i <= m; i++) if(!bel[i])
		for(int j = 1; j <= m; j++) if(!bel[j] && i != j) {
			bool flag = true;
			for(int k = 1; k <= n; k++) flag &= a[k][i] <= a[k][j];
			if(!flag) continue;
			dinic.add_edge(i, j + m, 1);
		}
	int K = 0;
	for(int i = 1; i <= m; i++) K += !bel[i];
	K -= dinic.maxflow(src, dst);
	printf("%d\n", K);
	for(int i = 1; i <= m; i++) if(!bel[i]) fa[i] = i;
	for(int u = 1; u <= m; u++) if(!bel[u])
		for(int i = dinic.head[u]; i; i = dinic.edge[i].nxt) {
			int v = dinic.edge[i].to - m;
			if(dinic.edge[i ^ 1].r && v <= m && !bel[v]) merge(u, v);
		}
	int c = 0;
	for(int i = 1; i <= m; i++) if(!bel[i] && find(i) == i) id[i] = ++c;
	for(int i = 1; i <= m; i++) if(!bel[i]) for(int j = 1; j <= n; j++) cnt[id[find(i)]][j] += a[j][i], tot[i] += a[j][i];
	for(int i = 1; i <= K; i++) {
		std::vector<int> vct;
		for(int j = 1; j <= n; j++) vct.push_back(j);
		std::sort(vct.begin(), vct.end(), [&](int x, int y) { return cnt[i][x] < cnt[i][y]; });
		for(int j = 1; j <= n; j++) pos[i][vct[j - 1]] = j;
	}
	for(int i = 1; i <= m; i++) printf("%d ", id[find(bel[i] ? bel[i] : i)]);
	puts("");
	for(int i = 1; i <= m; i++) printf("%d ", n - tot[bel[i] ? bel[i] : i] + 1);
	puts("");
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= K; j++) printf("%d ", pos[j][i]);
		puts("");
	}
	return 0;
}