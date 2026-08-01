#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 200 + 5;
const int M = 5000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

struct Edge { int to, nxt; LL r; } edge[M << 1];
int head[N], cur[N];
void add_edge(int u, int v, int r) { static int k = 2; edge[k] = (Edge){v, head[u], r}, head[u] = k++; }
int n, m, s, t;

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
} dinic;

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, 0); }
	printf("%lld\n", dinic.maxflow(n, s, t));
	return 0;
}