#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, Q;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], ek;
	void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }
} G;

int go[20][N], dep[N], dfn[N], out[N];


int main() {
#ifndef DEBUG
	freopen("lonely.in", "r", stdin);
	freopen("lonely.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		G = Graph(), lct = LCT(), G.ek = 1;
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) lct.nw_node();
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); G.add_edge(u, v), G.add_edge(v, u); }
		dfs(1, 0);
		for(int j = 1; j < 20; j++) for(int i = 1; i <= n; i++) go[j][i] = go[j - 1][go[j - 1][i]];
		while(Q--) {
			int t, u, v;
			scanf("%d%d%d", &t, &u, &v);
			if(t == 1) lct.modify(u, v);
			else printf("%d\n", lct.query(u, v));
		}
	}
	return 0;
}
