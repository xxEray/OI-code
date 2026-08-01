#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N], b[N], last[N];
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

std::priority_queue<std::pair<int, int>> q;
int vis[N];

std::vector<int> to[N];

int dfn[N], low[N], stk[N], bl[N];
int time_stamp, top, scc;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int v : to[u]) {
		if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
	}
	if(dfn[u] == low[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}

int ind[N];

int main() {
#ifndef DEBUG
	freopen("infect.in", "r", stdin);
	freopen("infect.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= n; i++) q.emplace(a[i], i);
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to, w = edge[i].w;
			if(a[u] < w) continue;
			if(a[v] < a[u] - w) a[v] = a[u] - w, q.emplace(a[v], v);
			to[u].emplace_back(v);
			// printf("%d -> %d\n", u, v);
		}
	}
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	for(int u = 1; u <= n; u++) for(int v : to[u]) if(bl[u] != bl[v]) ind[bl[v]]++;
	int cnt = 0;
	for(int i = 1; i <= scc; i++) cnt += (ind[i] == 0);
	printf("%d\n", cnt);
	return 0;
} /*
10
1 2 2 2 6 3 4 5 4 3
1 2 5
2 3 1
2 4 5
4 5 2
4 6 4
4 7 3
1 8 1
8 9 5
8 10 4
*/