#include <bits/stdc++.h>

const int N = 2e4 + 5;
const int M = 1e5 + 5;

int n, m;
struct Edge { int to, nxt; } edge[M << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int rt;
int dfn[N], low[N];
bool iscut[N];
int time_stamp;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	int son = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(!dfn[v]) {
			tarjan(v), low[u] = std::min(low[u], low[v]);
			if(u != rt && low[v] == dfn[u]) iscut[u] = true;
			son++;
		} else low[u] = std::min(low[u], dfn[v]);
	}
	if(u == rt && son >= 2) iscut[u] = true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(rt = i);
	// for(int i = 1; i <= n; i++) printf("%d: dfn = %d, low = %d\n", i, dfn[i], low[i]);
	int cut = 0;
	for(int i = 1; i <= n; i++) cut += iscut[i];
	printf("%d\n", cut);
	for(int i = 1; i <= n; i++) if(iscut[i]) printf("%d ", i);
	return 0;
}