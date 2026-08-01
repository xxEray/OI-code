#include <cstdio>
#include <algorithm>

const int N = 5e5 + 5;

int n, m;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dep[N];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
	}
}

struct SegNode { int f, g, ls, rs; } t[N];
struct SegmentTree {
	SegNode t[N << 2];
	void 
} seg;
int merge(int x, int y, int last) {
	if(!x || !y) return x ^ y;
	
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(dep[u] < dep[v]) std::swap(u, v);
		a[u] = std::max(a[u], dep[v]);
	}
	return 0;
}