#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

typedef long long LL;

const int N = 500 + 5;
const int FLOW_N = 2 * N + 3;
const int FLOW_M = N * N + 3 * N + 1;
const LL LLINF = 0x3f3f3f3f;

struct Line {
	LL x1, y1, x2, y2;
	LL length() { return floor(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) + 1e-8); }
	bool vertical() { return x1 == x2; }
} a[N];
int n, m;

struct Dinic {
	struct Edge { int to, nxt; LL r, w; } edge[FLOW_M << 1];
	int head[FLOW_N];
private:
	int cur[FLOW_N], ek;
	LL dep[FLOW_N];
	bool inq[FLOW_N];
	int n, src, dst;
	LL flow, cost;
	void add_one(int u, int v, LL c, LL w) { edge[ek] = (Edge){v, head[u], c, -w}, head[u] = ek++; }
	bool spfa() {
		std::queue<int> q;
		for(int i = 1; i <= n; i++) inq[i] = false, dep[i] = LLINF;
		dep[src] = 0, q.push(src), inq[src] = true;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				if(dep[v] > dep[u] + edge[i].w && edge[i].r) {
					dep[v] = dep[u] + edge[i].w;
					if(!inq[v]) q.push(v), inq[v] = true;
				}
			}
		}
		return dep[dst] != LLINF;
	}
	LL dfs(int u, LL in) {
		if(u == dst) return in;
		LL out = 0;
		inq[u] = true;
		for(int &i = cur[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(inq[v] || dep[v] != dep[u] + edge[i].w || !edge[i].r) continue;
			LL x = dfs(v, std::min(edge[i].r, in));
			edge[i].r -= x, edge[i ^ 1].r += x;
			in -= x, out += x;
			cost += x * edge[i].w;
		}
		if(!out) dep[u] = 0;
		inq[u] = false;
		return out;
	}
public:
	Dinic() : ek(2) {}
	void reset() { for(int i = 1; i <= n; i++) head[i] = 0; ek = 2; }
	void add_edge(int u, int v, LL c, LL w) { add_one(u, v, c, w), add_one(v, u, 0, -w); }
	std::pair<LL, LL> maxcost(int n_, int src_, int dst_) {
		n = n_, src = src_, dst = dst_;
		flow = cost = 0;
		while(spfa()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			flow += dfs(src, LLINF);
		}
		return std::make_pair(flow, -cost);
	}
} dinic;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld%lld%lld", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
	int src = 2 * n + 1, dst = 2 * n + 2, rsrc = 2 * n + 3;
	for(int i = 1; i <= n; i++) dinic.add_edge(i, i + n, 1, a[i].length());
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(i != j && a[i].x2 <= a[j].x1 && !(a[i].vertical() && a[j].vertical() && a[i].x1 == a[j].x1)) dinic.add_edge(i + n, j, 1, 0);
	dinic.add_edge(src, rsrc, m, 0);
	for(int i = 1; i <= n; i++) dinic.add_edge(rsrc, i, 1, 0), dinic.add_edge(i + n, dst, 1, 0);
	printf("%lld\n", dinic.maxcost(2 * n + 3, src, dst).second);
	return 0;
} /*
7 2
1 0 9 3
2 1 3 1
3 -1 3 2
5 1 5 15
5 1 5 20
5 1 10 1
3 1 10 1

2 1
0 0 0 1
0 0 0 2
*/