#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

bool vis[N];
std::vector<std::pair<int, int>> dfs_tree, bfs_tree;
void dfs(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
		int v = edge[i].to;
		dfs_tree.push_back({u, v});
		dfs(v);
	}
}
void bfs() {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) vis[i] = false;
	q.push(1), vis[1] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = edge[i].nxt) if(!vis[edge[i].to]) {
			int v = edge[i].to;
			vis[v] = true;
			bfs_tree.push_back({u, v});
			q.push(v);
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("conquer.in", "r", stdin);
	freopen("conquer.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1), bfs();
	assert((int)dfs_tree.size() == n - 1), assert((int)bfs_tree.size() == n - 1);
	for(auto [u, v] : dfs_tree) printf("%d %d\n", u, v);
	for(auto [u, v] : bfs_tree) printf("%d %d\n", u, v);
	return 0;
} /*
6 8
5 1
4 3
1 4
3 5
1 2
2 6
1 6
4 2
*/
