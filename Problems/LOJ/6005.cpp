#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

const int N = 500 + 5;
const int FLOW_N = N + 2;
const int FLOW_M = N * N + 2 * N;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

int f[N];
std::vector<int> last[N];

struct Dinic {
	struct Edge { int to, nxt; int r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	int dep[FLOW_N];
	void add_one_edge(int u, int v, int c) { edge[ek] = (Edge){v, head[u], c}, head[u] = ek++; }
	bool bfs() {
		std::queue<int> q;
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
	void reset() { memset(head, 0, sizeof(head)); ek = 2; }
	Dinic() : ek(2) {}
	void add_edge(int u, int v, int c) { /* printf("%d -> %d (w=%d)\n", u, v, c); */ add_one_edge(u, v, c), add_one_edge(v, u, 0); }
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
	scanf("%d", &n);
	if(n == 1) { puts("1\n1\n1"); return 0; }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		f[i] = 1;
		for(int j = 1; j < i; j++) if(a[j] <= a[i]) {
			if(f[j] + 1 > f[i]) f[i] = f[j] + 1, last[i].clear(), last[i].push_back(j);
			else if(f[j] + 1 == f[i]) last[i].push_back(j);
		}
		// printf("%d: f = %d, last = ", i, f[i]);
		// for(int j : last[i]) printf("%d ", j);
		// puts("");
	}
	int s = *std::max_element(f + 1, f + n + 1);
	printf("%d\n", s);
	int src = n + 1, dst = n + 2;
	for(int i = 1; i <= n; i++) for(int j : last[i]) dinic.add_edge(j, i, 1);
	for(int i = 1; i <= n; i++) if(f[i] == s) dinic.add_edge(i, dst, 1);
	for(int i = 1; i <= n; i++) if(f[i] == 1) dinic.add_edge(src, i, 1);
	printf("%d\n", dinic.maxflow(n + 2, src, dst));
	dinic.reset();
	for(int i = 1; i <= n; i++) for(int j : last[i]) dinic.add_edge(j, i, 1);
	for(int i = 1; i <= n; i++) if(f[i] == s) dinic.add_edge(i, dst, i == n ? INF : 1);
	for(int i = 1; i <= n; i++) if(f[i] == 1) dinic.add_edge(src, i, i == 1 ? INF : 1);
	printf("%d\n", dinic.maxflow(n + 2, src, dst));
	return 0;
}