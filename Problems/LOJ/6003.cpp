#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

const int MX = 5000 + 5;
const int FLOW_M = MX * MX + MX * 2;
const int FLOW_N = 2 * MX + 2;
const int INF = 0x3f3f3f3f;

int n;

struct Dinic {
	struct Edge { int to, nxt, r; } edge[FLOW_M << 1];
	int head[FLOW_N], cur[FLOW_N], ek;
	int dep[FLOW_N];
	int n, s, t;
	Dinic() : ek(2) {}
	void reset() { memset(head, 0, sizeof(head)), ek = 2; }
	void add_one_edge(int u, int v, int w) { edge[ek] = (Edge){v, head[u], w}, head[u] = ek++; }
	void add_edge(int u, int v, int w) { add_one_edge(u, v, w), add_one_edge(v, u, 0); }
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
		for(int &i = cur[u]; i && in; i = edge[i].nxt) if(dep[edge[i].to] == dep[u] + 1 && edge[i].r) {
			int v = edge[i].to;
			int w = dfs(v, std::min(in, edge[i].r));
			edge[i].r -= w, edge[i ^ 1].r += w;
			in -= w, out += w;
		}
		if(!out) dep[u] = 0;
		return out;
	}
	int maxflow(int n_, int s_, int t_) {
		n = n_, s = s_, t = t_;
		int ret = 0;
		while(bfs()) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			ret += dfs(s, INF);
		}
		return ret;
	}
	int mincut(int n_, int s_, int t_) { return maxflow(n_, s_, t_); }
} dinic;

bool check(int m) {
	dinic.reset();
	// printf("check %d\n", m);
	int s = m * 2 + 1, t = m * 2 + 2;
	for(int i = 1; i <= m; i++)
		for(int j = i + 1; j <= m; j++) {
			int sqij = round(sqrt(i + j));
			if(sqij * sqij != i + j) continue;
			dinic.add_edge(i, j + m, 1);
			// printf("%d -> %d\n", i, j);
		}
	for(int i = 1; i <= m; i++) dinic.add_edge(s, i, 1), dinic.add_edge(i + m, t, 1);
	return m - dinic.maxflow(m * 2 + 2, s, t) <= n;
}

int nxt[MX], beg[MX];
void get_ans(int m) {
	check(m);
	for(int i = 1; i <= m; i++) beg[i] = true;
	for(int i = 1; i <= m; i++) for(int j = dinic.head[i]; j; j = dinic.edge[j].nxt) if(dinic.edge[j ^ 1].r) {
		int v = dinic.edge[j].to;
		if(v == dinic.s) continue;
		nxt[i] = v - m, beg[v - m] = false;
	}
	for(int i = 1; i <= m; i++) if(beg[i]) {
		bool flag = false;
		for(int j = i; j; j = nxt[j]) flag ? putchar(' ') : flag = true, printf("%d", j);
		puts("");
	}
}

int main() {
	scanf("%d", &n);
	int l = 1, r = 1;
	while(check(r)) r <<= 1;
	r++;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	// printf("check(3) = %d\n", check(3));
	printf("%d\n", l - 1);
	get_ans(l - 1);
	return 0;
}