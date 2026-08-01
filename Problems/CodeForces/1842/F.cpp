#include <bits/stdc++.h>

const int N = 5000 + 5;

int n;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dep[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

int ans[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) {
		dep[i] = 0, dfs(i, 0);
		std::sort(dep + 1, dep + n + 1);
		int sum = 0;
		for(int j = 0; j <= n; j++) sum += dep[j], ans[j] = std::max(ans[j], (n - 1) * j - 2 * sum);
	}
	for(int i = 0; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}