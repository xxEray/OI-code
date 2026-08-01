#include <cstdio>
#include <algorithm>
#include <cstring>

#define CLEAR(arr) memset(arr, 0, sizeof(arr))

const int N = 2e5 + 5;

struct Node { int a, b, id; } a[N];
bool cmpa(Node x, Node y) { return x.a < y.a; }
bool cmpb(Node x, Node y) { return x.b < y.b; }
int n;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	void add_edge(int u, int v) { edge[k] = (Edge){v, head[u]}, head[u] = k++; }
} G, R;

int belong[N], vis[N];
int tot, tm;
void tarjan(int u) {
	static int stk[N], top = 0;
	static int low[N], dfn[N];
	vis[u] = 1;
	low[u] = dfn[u] = ++tm;
	stk[top++] = u;
	for(int i = G.head[u]; i; i = G.edge[i].nxt) {
		int v = G.edge[i].to;
		if(vis[v] == 0) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		} else if(vis[v] == 1) {
			low[u] = std::min(low[u], low[v]);
		}
	}
	if(low[u] == dfn[u]) {
		tot++;
		do {
			top--;
			vis[stk[top]] = 2;
			belong[stk[top]] = tot;
		} while(u != stk[top]);
	}
}

int sz[N];
int calc_size(int u) {
	if(sz[u]) return sz[u];
	sz[u] = 1;
	for(int i = R.head[u]; i; i = R.edge[i].nxt) sz[u] += calc_size(R.edge[i].to);
	// printf("calc_size(%d) = %d\n", u, sz[u]);
	return sz[u];
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		CLEAR(G.head), CLEAR(R.head), CLEAR(vis), CLEAR(sz), G.k = R.k = 1, tot = tm = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].a), a[i].id = i;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i].b);
		std::sort(a + 1, a + n + 1, cmpa);
		for(int i = 1; i < n; i++) G.add_edge(a[i + 1].id, a[i].id); // , printf("G: %d -> %d\n", a[i + 1].id, a[i].id);
		std::sort(a + 1, a + n + 1, cmpb);
		for(int i = 1; i < n; i++) if(a[i + 1].a <= a[i].a) G.add_edge(a[i + 1].id, a[i].id); // , printf("G: %d -> %d\n", a[i + 1].id, a[i].id);
		for(int i = 1; i <= n; i++) if(vis[i] == 0) tarjan(i);
		for(int u = 1; u <= n; u++)
			for(int i = G.head[u]; i; i = G.edge[i].nxt) {
				int v = G.edge[i].to;
				if(belong[u] != belong[v]) R.add_edge(belong[u], belong[v]); // , printf("R: %d -> %d\n", belong[u], belong[v]);
			}
		for(int i = 1; i <= n; i++) printf("%d", calc_size(belong[i]) == tot);
		puts("");
	}
	return 0;
} /*
4
1 3 2 4
2 1 4 3
*/