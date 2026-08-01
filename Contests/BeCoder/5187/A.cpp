#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 100 + 5;
const int M = 1000 + 5;
const int FLOW_N = 200 + 5;
const int FLOW_M = 5000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
std::vector<int> a[N];
int b[M], d[N];

struct Dinic {
private:
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
		for(int &i = cur[u]; i; i = edge[i].nxt) if(dep[u] + 1 == dep[edge[i].to] && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
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

int last[M];

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) {
		int k, x;
		scanf("%d", &k);
		while(k--) scanf("%d", &x), a[i].push_back(x);
		scanf("%d", &d[i]);
	}
	int src = n + 1, dst = n + 2;
	dinic.init(n + 2);
	for(int i = 1; i <= n; i++) {
		int tot = 0;
		for(int o = 0; o < (int)a[i].size(); o++) {
			int j = a[i][o];
			if(!last[j]) tot += b[j];
			else dinic.add_edge(last[j], i, LLINF);
			last[j] = i;
		}
		if(tot) dinic.add_edge(src, i, tot);
		dinic.add_edge(i, dst, d[i]);
	}
	printf("%lld\n", dinic.maxflow(src, dst));
	return 0;
}