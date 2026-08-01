#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int M = 2e6 + 5;

int n, m;
struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 2; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int rt;
int dfn[N], low[N], stk[N];
int time_stamp, top;
std::vector<std::vector<int>> vbcc;
void tarjan(int u, int fid) {
	// printf("tarjan %d\n", u);
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	for(int i = head[u]; i; i = edge[i].nxt) if(i != (fid ^ 1)) {
		int v = edge[i].to;
		if(!dfn[v]) {
			tarjan(v, i), low[u] = std::min(low[u], low[v]);
			if(low[v] > dfn[u]) {
				vbcc.emplace_back();
				do {
					top--;
					vbcc.back().emplace_back(stk[top]);
				} while(stk[top] != v);
			}
		} else low[u] = std::min(low[u], dfn[v]);
	}
	if(u == rt) {
		vbcc.emplace_back();
		while(top) vbcc.back().emplace_back(stk[--top]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(rt = i, 0);
	// for(int i = 1; i <= n; i++) printf("%d: dfn = %d, low = %d\n", i, dfn[i], low[i]);
	printf("%d\n", (int)vbcc.size());
	for(auto &vec : vbcc) {
		printf("%d ", (int)vec.size());
		for(int x : vec) printf("%d ", x);
		puts("");
	}
	return 0;
}