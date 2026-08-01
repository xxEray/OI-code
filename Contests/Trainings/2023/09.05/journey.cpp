#include <bits/stdc++.h>

typedef long long LL;

const int N = 300 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, Q;
LL dis[N][N];

struct Edge { int to, nxt, r; LL w; } edge[N * N * 20];
int head[N * 2], cur[N * 2];
void add_one_edge(int u, int v, int r, LL w) { static int k = 2; edge[k] = (Edge){v, head[u], r, w}, head[u] = k++; }
void add_edge(int u, int v, int r, LL w) { add_one_edge(u, v, r, w), add_one_edge(v, u, 0, -w); }

LL val[N * N], sum[N * N];
int cn;

int src, dst;
LL cost;

LL dep[N * 2];
bool inq[N * 2];
int dfs(int u, int in) {
	if(u == dst) {
		assert(in == 1);
		return in;
	}
	inq[u] = true;
	int out = 0;
	for(int &i = cur[u]; i; i = edge[i].nxt) if(!inq[edge[i].to] && edge[i].r && dep[edge[i].to] == dep[u] + edge[i].w) {
		int v = edge[i].to;
		int ret = dfs(v, std::min(in, edge[i].r));
		if(!ret) continue;
		edge[i].r -= ret, edge[i ^ 1].r += ret;
		in -= ret, out += ret;
		cost += ret * edge[i].w;
		if(!in) return out;
	}
	if(!out) dep[u] = -LLINF;
	inq[u] = false;
	return out;
}
bool spfa() {
	for(int i = 1; i <= 2 * n + 2; i++) dep[i] = LLINF, inq[i] = false;
	std::queue<int> q;
	dep[src] = 0, q.push(src), inq[src] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].r) {
			int v = edge[i].to;
			if(dep[v] <= dep[u] + edge[i].w) continue;
			dep[v] = dep[u] + edge[i].w;
			if(!inq[v]) q.push(v), inq[v] = true;
		}
	}
	for(int i = 1; i <= 2 * n + 2; i++) cur[i] = head[i];
	return dep[dst] < LLINF;
}


int main() {
#ifndef DEBUG
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : LLINF);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); dis[u][v] = std::min(dis[u][v], w); }
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j && dis[i][j] < LLINF) add_edge(i, j + n, 1, dis[i][j]);
	src = 2 * n + 1, dst = 2 * n + 2;
	for(int i = 1; i <= n; i++) add_edge(src, i, 1, 0), add_edge(i + n, dst, 1, 0);
	int flow = 0;
	while(spfa()) while(dfs(src, 1)) val[++cn] = cost;
	// printf("val: "); for(int i = 1; i <= cn; i++) printf("%lld ", val[i]); puts("");
	while(Q--) {
		LL c;
		scanf("%lld", &c);
		LL ans = LLINF;
		for(int i = 0; i <= cn; i++) ans = std::min(ans, val[i] + (n - i) * c);
		printf("%lld\n", ans);
	}
	return 0;
} /*
5 12 5
4 3 2323
1 5 2767
3 4 9253
4 3 4005
1 5 6067
2 5 8864
2 5 8580
4 1 9043
3 4 4890
3 5 1729
2 4 3825
4 3 2122
10546
13764
7778
9935
9413
*/