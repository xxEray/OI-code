#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD1 = 1e9 + 33;
const LL HSH1 = 1e9 + 21;
const LL MOD2 = 1e9 + 93;
const LL HSH2 = 1e9 + 87;

int n, m;
struct Edge { int to, nxt, w; } edge[N];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL power1[N], power2[N];

bool inf[N];
int vis[N], dfn[N], low[N];
int stk[N], top, time_stamp;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	vis[u] = 1;
	stk[top++] = u;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		if(stk[top - 1] == u) top--, vis[u] = 2;
		else {
			do {
				top--;
				vis[stk[top]] = 2;
				inf[stk[top]] = true;
			} while(stk[top] != u);
		}
	}
}

int f[N], g[N][21];
LL h1[N][21], h2[N][21], ans[N];
int compare(int i, int j) {
	int r = f[i];
	for(int k = 1; k <= r; k++)
		if(h1[i][0] == h1[j][0]) i = g[i][0], j = g[j][0];
		else return h1[i][0] < h1[j][0] ? i : j;
	return i;
	for(int k = 20; k >= 0; k--) if(r > (1 << k) && h1[i][k] == h1[j][k] && h2[i][k] == h2[j][k]) i = g[i][k], j = g[j][k];
	return h1[i][0] < h1[j][0] ? i : j;
}
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = 1;
	int v0 = 0, nh = 0;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		dfs(v);
		if(inf[v]) inf[u] = true;
		else if(!v0) v0 = v, nh = edge[i].w;
		else if(f[v0] != f[v]) { if(f[v] > f[v0]) v0 = v, nh = edge[i].w; }
		else if(edge[i].w != nh) { if(edge[i].w < nh) v0 = v, nh = edge[i].w; }
		else if(compare(v0, v) == v) v0 = v, nh = edge[i].w;
	}
	if(inf[u]) return;
	f[u] = f[v0] + 1;
	ans[u] = (nh + ans[v0] * 29) % 998244353;
	h1[u][0] = nh + 1, h2[u][0] = nh + 1, g[u][0] = v0;
	for(int j = 1; j <= 20; j++) {
		g[u][j] = g[g[u][j - 1]][j - 1];
		h1[u][j] = (h1[u][j - 1] + h1[g[u][j - 1]][j - 1] * power1[1 << (j - 1)]) % MOD1;
		h2[u][j] = (h2[u][j - 1] + h2[g[u][j - 1]][j - 1] * power2[1 << (j - 1)]) % MOD2;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w); if(u == v) inf[u] = true; }
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	// for(int i = 1; i <= n; i++) printf("inf[%d] = %d\n", i, inf[i]);
	for(int i = 1; i <= n; i++) vis[i] = 0;
	power1[0] = power2[0] = 1;
	for(int i = 1; i <= n; i++) power1[i] = power1[i - 1] * HSH1 % MOD1, power2[i] = power2[i - 1] * HSH2 % MOD2;
	for(int i = 1; i <= n; i++) dfs(i);
	for(int i = 1; i <= n; i++)
		if(inf[i]) puts("Infinity");
		else printf("%lld\n", ans[i] * 29 % 998244353);
	return 0;
} /*
5 7
4 1 5
2 1 7
3 4 2
4 5 3
4 5 1
3 5 1
5 2 4
*/