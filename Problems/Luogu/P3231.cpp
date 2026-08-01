#include <bits/stdc++.h>

const int N = 5e3 + 5;
const int N2 = 5000 / 17 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
std::vector<std::array<int, 3>> vct;
bool a[N][N];

int hash(int i, int j, int k) { return (i - 1) * m * K + (j - 1) * K + k; }

int src, dst;
struct Dinic {
	struct Edge { int to, nxt, r; } edge[N2 << 1];
	int head[N2], cur[N2], dep[N2], ek, tot;
	void clear() { ek = 2; for(int i = 1; i <= tot; i++) head[i] = 0; }
	void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int dfs(int u, int in) {
		if(u == dst) return in;
		int out = 0;
		for(int &i = cur[u]; i; i = edge[i].nxt) if(edge[i].r && dep[edge[i].to] == dep[u] + 1) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r));
			in -= ret, out += ret;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			if(!in) break;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	bool bfs() {
		for(int i = 1; i <= tot; i++) dep[i] = INF;
		std::queue<int> q;
		q.push(src), dep[src] = 0;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].r && dep[edge[i].to] == INF) {
				int v = edge[i].to;
				dep[v] = dep[u] + 1, q.push(v);
			}
		}
		for(int i = 1; i <= tot; i++) cur[i] = head[i];
		return dep[dst] != INF;
	}
	int flow() {
		int ret = 0;
		while(bfs()) ret += dfs(src, INF);
		return ret;
	}
} dinic;

int main() {
	// freopen("/home/eray/下载/input1.txt", "r", stdin);
	int T; scanf("%d", &T);
	while(T--) {
		vct.clear();
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= K; k++)
			{ int x; scanf("%d", &x); if(x) vct.push_back({i, j, k}); }
		if(n <= m && n <= K) {
			for(auto &p : vct) std::swap(p[0], p[2]);
			std::swap(n, K);
		} else if(m <= n && m <= K) {
			for(auto &p : vct) std::swap(p[1], p[2]);
			std::swap(m, K);
		}
		// printf("K = %d\n", K);
		dinic.tot = n + m + 2;
		src = n + m + 1, dst = n + m + 2;
		int U = (1 << K) - 1;
		int ans = INF;
		for(int s = 0; s <= U; s++) {
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = false;
			dinic.clear();
			for(int i = 1; i <= n; i++) dinic.add_edge(src, i, 1);
			for(int i = 1; i <= m; i++) dinic.add_edge(i + n, dst, 1);
			for(auto [x, y, z] : vct) if(~s >> (z - 1) & 1) a[x][y] = true;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(a[i][j]) dinic.add_edge(i, j + n, 1);
			ans = std::min(ans, dinic.flow() + __builtin_popcount(s));
		}
		printf("%d\n", ans);
	}
	return 0;
}