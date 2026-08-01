#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}
int a[N];
int n;

int sum[N], size[N];
LL ans[N];

inline LL count(int x) { return (LL)x * (x + 1) / 2; }

void dfs(int u, int fa) {
	size[u] = 1;
	int t = sum[a[u]];
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			sum[a[u]] = 0;
			dfs(v, u);
			size[u] += size[v];
			ans[a[u]] -= count(size[v] - sum[a[u]]);
		}
	sum[a[u]] = t + size[u];
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("%lld\n", ans[i] + count(n) - count(n - sum[i]));
	return 0;
}