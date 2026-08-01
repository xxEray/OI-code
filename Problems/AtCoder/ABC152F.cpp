#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 50 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int q[N][2];
int n, m;

int fa[N];
void get_fa(int u) { for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) fa[edge[i].to] = u, get_fa(edge[i].to); }
int lca[N][N], vis[N];

LL mask[N];

int size(int s) { int ret = 0; for(int i = 0; i < 30; i++) ret += s >> i & 1; return ret; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i][0], &q[i][1]);
	get_fa(1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		for(int k = 1; k <= n; k++) vis[k] = false;
		int u = i, v = j;
		if(u == v) { lca[u][v] = u; continue; }
		vis[u] = vis[v] = true;
		while(true) {
			u = fa[u];
			if(u) {
				if(vis[u]) { lca[i][j] = u; break; }
				vis[u] = true;
			}
			v = fa[v];
			if(v) {
				if(vis[v]) { lca[i][j] = v; break; }
				vis[v] = true;
			}
		}
	}
	for(int i = 1; i <= m; i++) {
		int u = q[i][0], v = q[i][1];
		for(int j = u; j != lca[u][v]; j = fa[j]) mask[j] |= 1 << (i - 1);
		for(int j = v; j != lca[u][v]; j = fa[j]) mask[j] |= 1 << (i - 1);
	}
	LL ans = 0;
	int U = (1 << m) - 1;
	for(int s = 0; s <= U; s++) {
		int cnt = 0;
		for(int i = 2; i <= n; i++) if(!(mask[i] & s)) cnt++;
		if(size(s) & 1) ans -= 1LL << cnt;
		else ans += 1LL << cnt;
	}
	printf("%lld\n", ans);
	return 0;
}