#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;

const int N = 600 + 5;
const int M = N * N;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N][N];
int n, m, s, t;

int hash(int x, int y) { return (x - 1) * m + y; }

std::vector<int> to[N], vct;
bool vis[N];
int ind[N];
void toposort() {
	for(int i = 1; i <= n * m; i++) if(!ind[i]) vct.push_back(i), vis[i] = true;
	while(!vct.empty()) {
		int u = vct.back(); vct.pop_back();
		for(int v : to[u]) {
			ind[v]--;
			if(!ind[v]) vis[v] = true, vct.push_back(v);
		}
	}
}

struct Edge { int to, nxt; LL r; } edge[M << 1];
int head[N], cur[N];
void add_edge(int u, int v, LL r) { static int k = 2; edge[k] = (Edge){v, head[u], r}, head[u] = k++; }

struct Dinic {
	int n, s, t;
	int dep[N];
	std::queue<int> q;
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
	LL maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		LL ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, LLINF);
		}
		return ret;
	}
	inline LL mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); }
} dinic;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int c; scanf("%lld%d", &a[i][j], &c);
			while(c--) { int x, y; scanf("%d%d", &x, &y); to[hash(i, j)].push_back(hash(x + 1, y + 1)); }
		}
	for(int i = 1; i <= n; i++) for(int j = 2; j <= m; j++) to[hash(i, j)].push_back(hash(i, j - 1));
	for(int i = 1; i <= n * m; i++) for(int j : to[i]) ind[j]++;
	toposort();
	for(int i = 1; i <= n * m; i++) for(int j : to[i]) if(vis[i] && vis[j]) add_edge(j, i, LLINF), add_edge(i, j, 0);
	s = n * m + 1, t = n * m + 2;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(vis[hash(i, j)]) {
		if(a[i][j] >= 0) add_edge(s, hash(i, j), a[i][j]), add_edge(hash(i, j), s, 0);
		else add_edge(hash(i, j), t, -a[i][j]), add_edge(t, hash(i, j), 0);
	}
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(vis[hash(i, j)] && a[i][j] >= 0) ans += a[i][j];
	// printf("dinic = %lld\n", dinic.mincut(n * m + 2, s, t));
	printf("%lld\n", ans - dinic.mincut(n * m + 2, s, t));
	return 0;
}