#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long LL;

const int N = 100 + 5;
const int FLOW_N = N + 2; // vertice count
const int FLOW_M = N * N + N * 2; // edge count
const int PRIME = 2e7 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int a[N];
LL b[N];
int n;

bool isprm[PRIME];
std::vector<int> prime;
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) if(isprm[i]) {
		prime.push_back(i);
		for(int j = i + i; j <= mx; j += i) isprm[j] = false;
	}
}

struct Dinic {
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
	Dinic() : ek(2) {}
	void add_edge(int u, int v, LL c) { add_one_edge(u, v, c), add_one_edge(v, u, 0); }
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

int main() {
	sieve(2e7);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%lld", &a[i], &b[i]);
	int src = n + 1, dst = n + 2;
	for(int i = 1; i <= n; i++)
		if(a[i] == 1);
		else if(a[i] & 1) dinic.add_edge(src, i, b[i]);
		else dinic.add_edge(i, dst, b[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if((a[i] & 1) && !(a[j] & 1) && isprm[a[i] + a[j]] && a[i] != 1)
			dinic.add_edge(i, j, LLINF);
	LL ans = 0;
	ans += dinic.maxflow(n + 2, src, dst);
	int e = 0;
	for(int i = 1; i <= n; i++) if(a[i] == 1) {
		dinic.add_edge(src, i, b[i]), e = (dinic.ek - 1) ^ 1;
		for(int j = 1; j <= n; j++) if(!(a[j] & 1) && isprm[a[j] + 1])
			dinic.add_edge(i, j, LLINF);
	}
	ans += dinic.maxflow(n + 2, src, dst);
	// printf("e = %d\n", e);
	if(e) ans += dinic.edge[e].r / 2;
	// printf("one = %d, v1 = %d, v2 = %d\n", one, v1, v2);
	printf("%lld\n", ans);
	return 0;
}