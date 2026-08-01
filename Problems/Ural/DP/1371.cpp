#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e4 + 5;

struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) {
	static int k = 1;
	edge[k] = (Edge){v, head[u], w};
	head[u] = k++;
}

int n;

int size[N];
LL ans;

void dfs(int u, int fa) {
	size[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			dfs(v, u);
			size[u] += size[v];
			ans += (LL)edge[i].w * size[v] * (n - size[v]);
		}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	dfs(1, 0);
	printf("%.5lf\n", (double)ans / ((LL)n * (n - 1) / 2));
	return 0;
}