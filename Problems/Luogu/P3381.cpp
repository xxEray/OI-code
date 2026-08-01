#include <cstdio>
#include <algorithm>
#include <queue>

typedef int LL;

const int FLOW_N = 5e3 + 5; // vertice count
const int FLOW_M = 5e4 + 5; // edge count
const LL LLINF = 0x3f3f3f3f;

int n, m, src, dst;

struct Dinic {
private:
	struct Edge { int to, nxt; LL r, w; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int n, s, t;
	LL dep[FLOW_N];
	bool inq[FLOW_N];
	std::queue<int> q;
	LL flow, cost;
	void add_one_edge(int u, int v, LL c, LL w) { edge[ek] = (Edge){v, head[u], c, w}, head[u] = ek++; }
	bool spfa() {
		for(int i = 1; i <= n; i++) dep[i] = LLINF;
		dep[s] = 1, q.push(s), inq[s] = true;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for(int i = head[u]; i; i = edge[i].nxt) if(dep[edge[i].to] > dep[u] + edge[i].w && edge[i].r) {
				int v = edge[i].to;
				dep[v] = dep[u] + edge[i].w;
				if(!inq[v]) q.push(v), inq[v] = true;
			}
		}
		return dep[t] != LLINF;
	}
	LL dfs(int u, LL in) {
		if(u == t) return in;
		inq[u] = true;
		LL out = 0;
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(!inq[edge[i].to] && dep[edge[i].to] == dep[u] + edge[i].w && edge[i].r) {
			int v = edge[i].to;
			LL ret = dfs(v, std::min(in, edge[i].r));
			if(!ret) continue;
			edge[i].r -= ret, edge[i ^ 1].r += ret;
			in -= ret, out += ret;
			cost += ret * edge[i].w;
		}
		if(!out) dep[u] = 0;
		inq[u] = false;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void add_edge(int u, int v, LL c, LL w) { add_one_edge(u, v, c, w), add_one_edge(v, u, 0, -w); }
	std::pair<LL, LL> mincost(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			flow += dfs(s, LLINF);
		}
		return {flow, cost};
	}
} dinic;

int main() {
	// freopen("D:/Useless/Temp/in.txt", "r", stdin);
	scanf("%d%d%d%d", &n, &m, &src, &dst);
	for(int i = 1; i <= m; i++) { int u, v, c, w; scanf("%d%d%d%d", &u, &v, &c, &w); dinic.add_edge(u, v, c, w);}
	auto ans = dinic.mincost(n, src, dst);
	printf("%d %d\n", ans.first, ans.second);
	return 0;
}