// or also P2762
#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 50 + 5;
const int FLOW_N = N * 2 + 2; // vertice count
const int FLOW_M = N * N + 2 * N; // edge count
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

char str[10005];
int n, m;

struct Dinic {
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
	Dinic() : ek(2) {}
	void add_edge(int u, int v, LL c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	LL maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		LL ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, LLINF);
		}
		return ret;
	}
	inline LL mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); } // mincut = maxflow
} dinic;

int main() {
	scanf("%d%d", &m, &n);
	LL sum = 0;
	int s = n + m + 1, t = n + m + 2;
	for(int i = 1; i <= m; i++) {
		LL v; scanf("%lld", &v);
		sum += v, dinic.add_edge(s, i, v);
		int x, c = 0, tc;
		fgets(str, 10000, stdin);
		while(sscanf(str + c, "%d%n", &x, &tc) == 1) dinic.add_edge(i, m + x, LLINF), c += tc;
	}
	for(int i = 1; i <= n; i++) { LL v; scanf("%lld", &v), dinic.add_edge(m + i, t, v); }
	LL ans = sum - dinic.mincut(n + m + 2, s, t);
	bool flag;
	flag = false;
	for(int i = dinic.head[s]; i; i = dinic.edge[i].nxt) {
		int v = dinic.edge[i].to;
		if(dinic.dep[v]) flag ? putchar(' ') : (flag = true), printf("%d", v);
	}
	puts("");
	flag = false;
	for(int i = dinic.head[t]; i; i = dinic.edge[i].nxt) {
		int v = dinic.edge[i].to;
		if(dinic.dep[v]) flag ? putchar(' ') : (flag = true), printf("%d", v - m);
	}
	puts("");
	printf("%lld\n", ans);
	return 0;
}