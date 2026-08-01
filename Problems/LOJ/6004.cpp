#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 150 + 5;
const int M = 270 + 5;
const int FLOW_N = N + M + 2; // vertice count
const int FLOW_M = N * M + N + M; // edge count
const int INF = 0x3f3f3f3f;

int a[N], b[N];
int n, m;

struct Dinic {
	struct Edge { int to, nxt; int r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	std::queue<int> q;
	void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
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
	int dfs(int u, int in) {
		if(u == t) return in;
		int out = 0;
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	Dinic() : ek(2) {}
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	inline int mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); } // mincut = maxflow
} dinic;

int main() {
	scanf("%d%d", &n, &m);
	int s = n + m + 1, t = n + m + 2;
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), dinic.add_edge(s, i, a[i]), sum += a[i];
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]), dinic.add_edge(i + n, t, b[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) dinic.add_edge(i, j + n, 1);
	int ret = dinic.maxflow(n + m + 2, s, t);
	if(ret < sum) { puts("0"); return 0; }
	puts("1");
	for(int i = 1; i <= n; i++) {
		bool flag = false;
		for(int j = dinic.head[i]; j; j = dinic.edge[j].nxt) if(dinic.edge[j ^ 1].r) {
			int v = dinic.edge[j].to;
			if(v == s) continue;
			if(flag) putchar(' '); else flag = true;
			printf("%d", v - n);
		}
		puts("");
	}
	return 0;
}