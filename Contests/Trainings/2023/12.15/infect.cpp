#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;

int n;
int a[N];
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int dfn1[N], dfl[2 * N], time_stamp1;
LL dep[N];
void dfs(int u, int f) {
	dfn1[u] = ++time_stamp1, dfl[dfn1[u]] = u;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != f) {
		int v = edge[i].to;
		dep[v] = dep[u] + edge[i].w;
		dfs(v, u);
		dfl[++time_stamp1] = u;
	}
}
LL go[21][2 * N];
void binary_lifting() {
	for(int i = 1; i <= 2 * n; i++) go[0][i] = dep[dfl[i]];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= 2 * n; i++)
			go[j][i] = std::min(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}
LL dist(int u, int v) {
	if(u == v) return 0;
	int l = dfn1[u], r = dfn1[v];
	if(l > r) std::swap(l, r);
	int k = 31 ^ __builtin_clz(r - l + 1);
	return dep[u] + dep[v] - 2 * std::min(go[k][l], go[k][r - (1 << k) + 1]);
}

std::vector<int> to[N];

int vis[N], dfn[N], low[N], stk[N], bl[N];
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
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < n; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	dfs(1, 0), binary_lifting();
	for(int u = 1; u <= n; u++) for(int v = 1; v <= n; v++) if(u != v && a[u] >= dist(u, v)) to[u].emplace_back(v); // , printf("%d -> %d\n", u, v);
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	for(int u = 1; u <= n; u++) for(int v : to[u]) if(bl[u] != bl[v]) ind[bl[v]]++;
	int cnt = 0;
	for(int i = 1; i <= scc; i++) cnt += (ind[i] == 0);
	printf("%d\n", cnt);
	return 0;
}