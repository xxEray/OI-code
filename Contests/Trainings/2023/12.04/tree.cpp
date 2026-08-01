// http://mna.wang/contest/212/problem/1

#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, Q, rt;
LL a[N], b[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL f[3][N], ans[N], addition[N];

void dfs(int u, int fa, int dep) {
	LL mx = -LLINF;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u, dep + 1);
		f[0][u] += std::max({f[0][v], f[1][v] + b[v], f[2][v] + b[v]});
		f[1][u] += std::max({f[0][v], f[1][v] + a[v], f[2][v] + b[v]});
		mx = std::max(mx, f[0][v] - std::max({f[0][v], f[1][v] + a[v], f[2][v] + b[v]}));
	}
	f[2][u] = f[1][u] + mx;
	ans[dep] += std::max({f[0][u], f[1][u] + b[u], f[2][u] + b[u]});
	addition[dep] += b[u];
}

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]), b[i] = std::max(b[i], a[i]);
	scanf("%d", &rt);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(rt, 0, 0);
	for(int i = 1; i <= n; i++) addition[i] += addition[i - 1];
	while(Q--) {
		int x;
		scanf("%d", &x);
		printf("%lld\n", ans[x] + (x ? addition[x - 1] : 0));
	}
	return 0;
} /*
6 3
9 8 1 8 9 5
6 6 9 10 1 7
1
2 1
3 2
4 1
5 4
6 5
1
2
3
*/