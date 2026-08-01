#include <cstdio>
#include <algorithm>
#include <deque>
#include <vector>

const int N = 1e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int a[N];
int n, m;

std::deque<int> ans[N];

struct Query { int id, k; };
std::vector<Query> query[N];
int out[N];
void dfs(int u, int fa) {
	ans[u].push_back(a[u]);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		for(int tmp : ans[v]) ans[u].push_back(tmp);
		std::sort(ans[u].begin(), ans[u].end());
		while(ans[u].size() > 20) ans[u].pop_front();
	}
	for(Query q : query[u]) out[q.id] = ans[u].end()[-q.k];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= m; i++) { int u, k; scanf("%d%d", &u, &k); query[u].push_back({i, k}); }
	dfs(1, 0);
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
}