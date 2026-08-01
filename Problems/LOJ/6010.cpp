#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

typedef long long LL;

const int N = 20 + 5;
const int FLOW_N = N * N * 4 + 2; // vertice count
const int FLOW_M = N * N * 6; // edge count
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int a[N][N * 2], hash[N][N * 2];
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
		dep[s] = 0, q.push(s), inq[s] = true;
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
	void reset() { memset(head, 0, sizeof(head)), ek = 2; }
	Dinic() : ek(2) {}
	void add_edge(int u, int v, LL c, LL w) { add_one_edge(u, v, c, -w), add_one_edge(v, u, 0, w); }
	std::pair<LL, LL> maxcost(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			flow += dfs(s, LLINF);
		}
		return {flow, -cost};
	}
} dinic;

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m + i - 1; j++) scanf("%d", &a[i][j]);
	int cnt = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m + i - 1; j++) hash[i][j] = ++cnt;
	src = cnt * 2 + 1, dst = cnt * 2 + 2;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m + i - 1; j++) {
		dinic.add_edge(hash[i][j], hash[i][j] + cnt, 1, a[i][j]);
		if(hash[i + 1][j]) dinic.add_edge(hash[i][j] + cnt, hash[i + 1][j], 1, 0);
		if(hash[i + 1][j + 1]) dinic.add_edge(hash[i][j] + cnt, hash[i + 1][j + 1], 1, 0);
	}
	for(int j = 1; j <= m; j++) dinic.add_edge(src, hash[1][j], 1, 0);
	for(int j = 1; j <= n + m - 1; j++) dinic.add_edge(hash[n][j] + cnt, dst, 1, 0);
	printf("%lld\n", dinic.maxcost(cnt * 2 + 2, src, dst).second);
	dinic.reset();
	src = cnt + 1, dst = cnt + 2;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m + i - 1; j++) {
		if(hash[i + 1][j]) dinic.add_edge(hash[i][j], hash[i + 1][j], 1, a[i + 1][j]);
		if(hash[i + 1][j + 1]) dinic.add_edge(hash[i][j], hash[i + 1][j + 1], 1, a[i + 1][j + 1]);
	}
	for(int j = 1; j <= m; j++) dinic.add_edge(src, hash[1][j], 1, a[1][j]);
	for(int j = 1; j <= n + m - 1; j++) dinic.add_edge(hash[n][j], dst, LLINF, 0);
	printf("%lld\n", dinic.maxcost(cnt + 2, src, dst).second);
	dinic.reset();
	src = cnt + 1, dst = cnt + 2;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m + i - 1; j++) {
		if(hash[i + 1][j]) dinic.add_edge(hash[i][j], hash[i + 1][j], LLINF, a[i + 1][j]);
		if(hash[i + 1][j + 1]) dinic.add_edge(hash[i][j], hash[i + 1][j + 1], LLINF, a[i + 1][j + 1]);
	}
	for(int j = 1; j <= m; j++) dinic.add_edge(src, hash[1][j], 1, a[1][j]);
	for(int j = 1; j <= n + m - 1; j++) dinic.add_edge(hash[n][j], dst, LLINF, 0);
	printf("%lld\n", dinic.maxcost(cnt + 2, src, dst).second);
	return 0;
}