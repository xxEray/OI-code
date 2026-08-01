#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

const int N = 3e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) {
	static int k = 1;
	edge[k] = (Edge){v, head[u]};
	head[u] = k++;
}
int n, m, Q, K;

// std::vector<int> stk;
// int low[N], dfn[N], vis[N];
// void tarjan(int u) {
// 	static int time = 0;
// 	low[u] = dfn[u] = ++time;
// 	stk.push_back(u);
// 	for(int i = head[u]; i; i = edge[i].nxt)
// 		if(edge[i].to != u)
// }

namespace SolveN5Q5 {
	bool flag;
	bool vis[N];
	void dfs(int u, int fa, int find) {
		// printf("dfs %d ", u);
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt)
			if(edge[i].to != fa) {
				int v = edge[i].to;
				if(v == find) vis[v] = flag = true;
				else dfs(v, u, find);
				if(flag) return;
			}
		vis[u] = false;
	}
	void main() {
		while(Q--) {
			int u, v;
			scanf("%d%d", &u, &v);
			flag = false;
			for(int i = 1; i <= n; i++) vis[i] = false;
			dfs(u, 0, v);
			int ans = 0;
			for(int i = 1; i <= n; i++) ans += vis[i];
			printf("%d\n", flag ? ans : 0);
		}
	}
}

int main() {
// #ifndef DEBUG
	freopen("celebration.in", "r", stdin);
	freopen("celebration.out", "w", stdout);
// #endif
	scanf("%d%d%d%d", &n, &m, &Q, &K);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
	}
	if(n <= 5 && Q <= 5) { SolveN5Q5::main(); return 0; }
	return 0;
} /*
5 6 4 0
1 2
1 3
1 4
2 5
4 5
5 4
1 4
2 3
1 2
3 4

*/