#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], b[N];
int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N];
void dfs(int u) {

}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) add_edge(a[i], b[i]);
	return 0;
}