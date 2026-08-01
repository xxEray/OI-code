#include <cstdio>
#include <algorithm>
#include <set>

const int N = 2e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n;

int dep[N], fa[N];

void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u, dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1);
	std::set<std::pair<int, int>> st;
	for(int i = 1; i <= n; i++) if(dep[i] > 2) st.insert({dep[i], i});
	int ans = 0;
	while(!st.empty()) {
		int u = st.rbegin()->second;
		u = fa[u];
		st.erase({dep[u], u});
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			st.erase({dep[v], v});
		}
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}