#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int FLOW_N = 2 * N + 2;
const int FLOW_M = 2 * N;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N];

int p[N], q[N];

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
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			int ret = dfs(v, std::min(in, edge[i].r));
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
	void add_edge(int u, int v, int c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
	int maxflow(int s_, int t_) {
		s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	inline int mincut(int s_, int t_) { return maxflow(s_, t_); } // mincut = maxflow
} dinic;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i]++;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), b[i]++;
	for(int i = 1; i <= n; i++) if(!p[i]) {
		int j;
		for(j = a[i]; j != i; j = a[j]) if(p[j]) p[i] = p[j];
		if(!p[i]) p[i] = i;
	}
	for(int i = 1; i <= n; i++) if(!q[i]) {
		int j;
		for(j = b[i]; j != i; j = b[j]) if(q[j]) q[i] = q[j];
		if(!q[i]) q[i] = i;
	}
	// printf("p: "); for(int i = 1; i <= n; i++) printf("%d ", p[i]); puts("");
	// printf("q: "); for(int i = 1; i <= n; i++) printf("%d ", q[i]); puts("");
	int src = 2 * n + 1, dst = 2 * n + 2;
	dinic.init(2 * n + 2);
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] == b[i] && a[i] == i) sum++;
		else if(a[i] == i && b[i] != i) dinic.add_edge(src, q[i] + n, 1);
		else if(a[i] != i && b[i] == i) dinic.add_edge(p[i], dst, 1);
		else if(a[i] != b[i] && a[i] != i && b[i] != i) dinic.add_edge(p[i], q[i] + n, 1);
		else if(a[i] == b[i] && a[i] != i) dinic.add_one_edge(p[i], q[i] + n, 1), dinic.add_one_edge(q[i] + n, p[i], 1);
	}
	printf("%d\n", n - (sum + dinic.maxflow(src, dst)));
	return 0;
} /*
1
4
30 2 3 5
*/