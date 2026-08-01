#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

#define SZ(x) ((int)(x).size())

typedef long long LL;

const int N = 20 + 5;
const int M = 20 + 5;
const int T_MAX = 1000;
const int FLOW_N = N * T_MAX;
const int FLOW_M = M * N * T_MAX;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

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
	void reset() { ek = 2; memset(head, 0, sizeof(head)); }
	void add_edge(int u, int v, LL c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); /* printf("%d -> %d (c=%lld)\n", u, v, c); */ }
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

int n, m, K;
std::vector<int> stat[N];
int a[N];

int hash(int sta, int tm) { return (tm - 1) * (n + 2) + sta; }
bool check(int time_lim) {
	dinic.reset();
	for(int j = 1; j <= m; j++) {
		int tm = 1, k = 0;
		while(tm < time_lim) {
			int nk = (k + 1) % SZ(stat[j]);
			dinic.add_edge(hash(stat[j][k], tm), hash(stat[j][nk], tm + 1), a[j]);
			tm++, k = nk;
		}
	}
	for(int i = 1; i < time_lim; i++)
		for(int j = 1; j <= n + 2; j++)
			dinic.add_edge(hash(j, i), hash(j, i + 1), LLINF);
	int src = hash(1, time_lim + 1), dst = hash(2, time_lim + 1);
	dinic.add_edge(src, hash(n + 1, 1), K);
	dinic.add_edge(hash(n + 2, time_lim), dst, LLINF);
	return dinic.maxflow(dst /* `dst` is the max id */, src, dst) == K;
}

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
		int t, x; scanf("%d", &t);
		while(t--) {
			scanf("%d", &x);
			if(x == 0) x = n + 1;
			if(x == -1) x = n + 2;
			stat[i].push_back(x);
		}
	}
	int l = 1, r = T_MAX;
	while(l < r) {
		// puts("-----------------");
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l == T_MAX ? 0 : l - 1);
	return 0;
}