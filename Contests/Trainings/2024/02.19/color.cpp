#include <bits/stdc++.h>

int n, m, Q, C;

namespace Subtask1 {
	const int N = 1000 + 5;
	const int INF = 0x3f3f3f3f;
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N];
	void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
	int a[N], d[N];
	int dis[N];
	void bfs() {
		std::deque<int> q;
		for(int i = 1; i <= n; i++) dis[i] = INF;
		dis[1] = 0, q.push_back(1);
		while(!q.empty()) {
			int u = q.front();
			q.pop_front();
			for(int i = head[u]; i; i = edge[i].nxt) {
				int v = edge[i].to;
				if(dis[v] != INF) continue;
				if(a[u] == a[v]) dis[v] = dis[u], q.push_front(v);
				else dis[v] = dis[u] + 1, q.push_back(v);
			}
		}
		int ans = INF;
		for(int i = 2; i <= n; i++) if(d[i] == 1) ans = std::min(ans, dis[i]);
		printf("%d\n", ans);
	}
	void main() {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); d[u]++, d[v]++; }
		bfs();
		while(Q--) {
			int p, x;
			scanf("%d%d", &p, &x);
			a[p] = x;
			bfs();
		}
	}
}

namespace Subtask2 {
	const int N = 1e5 + 5;
	const int INF = 0x3f3f3f3f;
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N];
	void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
	int a[N], b[N];
	int fa[N];
	std::vector<int> leaf[N];
	int cn;
	void dfs(int u) {
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
			int v = edge[i].to;
			fa[v] = u;
			dfs(v);
			leaf[u].insert(leaf[u].end(), leaf[v].begin(), leaf[v].end());
		}
		if(leaf[u].empty()) leaf[u].emplace_back(++cn);
	}
	void main() {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		dfs(1);
		for(int i = 2; i <= n; i++) if(a[i] != a[fa[i]]) for(int v : leaf[i]) b[v]++;
		int ans = INF;
		for(int i = 1; i <= cn; i++) ans = std::min(ans, b[i]);
		printf("%d\n", ans);
		while(Q--) {
			int u, x;
			scanf("%d%d", &u, &x);
			if(u != 1 && a[u] != a[fa[u]]) for(int v : leaf[u]) b[v]--;
			for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
				int v = edge[i].to;
				if(a[u] != a[v]) for(int w : leaf[v]) b[w]--;
			}
			a[u] = x;
			if(u != 1 && a[u] != a[fa[u]]) for(int v : leaf[u]) b[v]++;
			for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
				int v = edge[i].to;
				if(a[u] != a[v]) for(int w : leaf[v]) b[w]++;
			}
			int ans = INF;
			for(int i = 1; i <= cn; i++) ans = std::min(ans, b[i]);
			printf("%d\n", ans);
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &Q, &C);
	if(std::max({n, m, Q, C}) <= 1000) Subtask1::main();
	else Subtask2::main();
	return 0;
}
