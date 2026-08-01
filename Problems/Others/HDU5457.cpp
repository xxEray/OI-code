#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <algorithm>

typedef long long LL;
const int FLOW_N = 1e5 + 5;
const int FLOW_M = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;

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

int hsh[2][11][3000];
LL val[2][11][3000];

int main() {
	int T, _case = 0; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		int tot = 0;
		for(int t = 0; t <= 1; t++) for(int d = 0; d <= 8; d++) for(int x = 0; x < (1 << d); x++) hsh[t][d][x] = ++tot, val[t][d][x] = LLINF;
		dinic.init(tot);
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); dinic.add_edge(hsh[0][8][x], hsh[1][8][x], LLINF); }
		while(m--) {
			char t[2], s[10];
			LL w;
			scanf("%s%s%lld", t, s, &w);
			int d = 0;
			while(s[d]) d++;
			int x = 0;
			for(int i = 0; i < d; i++) x += (s[d - i - 1] - '0') << i;
			if(t[0] == 'P') val[0][d][x] = std::min(val[0][d][x], w);
			else val[1][d][x] = std::min(val[1][d][x], w);
		}
		for(int d = 1; d <= 8; d++) for(int x = 0; x < (1 << d); x++) {
			dinic.add_edge(hsh[0][d - 1][x >> 1], hsh[0][d][x], val[0][d][x]);
			dinic.add_edge(hsh[1][d][x], hsh[1][d - 1][x & ((1 << (d - 1)) - 1)], val[1][d][x]);
		}
		LL ans = dinic.mincut(hsh[0][0][0], hsh[1][0][0]);
		printf("Case #%d: %lld\n", ++_case, ans >= LLINF ? -1LL : ans);
	}
	return 0;
}