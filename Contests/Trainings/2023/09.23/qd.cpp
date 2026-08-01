#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;
int a[N], b[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N]; LL val[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	val[y] += val[x];
	fa[x] = y;
}

bool exist[N];
LL out[N];

int main() {
#ifndef DEBUG
	freopen("qd.in", "r", stdin);
	freopen("qd.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) fa[i] = i, val[i] = a[i];
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		out[i] = ans;
		int u = b[i];
		exist[u] = true;
		for(int j = head[u]; j; j = edge[j].nxt) {
			int v = edge[j].to;
			if(exist[v]) merge(u, v);
		}
		ans = std::max(ans, val[find(u)]);
	}
	for(int i = 1; i <= n; i++) printf("%lld\n", out[i]);
	return 0;
} /*
6 7
1 1 4 5 1 4
1 2
3 4
4 5
5 6
3 6
3 5
4 6
4 5 3 6 1 2
*/