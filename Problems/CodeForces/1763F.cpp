#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::vector<int> to[N * 2];
int dfn[N], low[N], stk[N], bl[N];
int time_stamp, top, vcc;
int val[N], ff[N];
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(dfn[v]) low[u] = std::min(low[u], dfn[v]);
		else {
			ff[v] = u;
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if(low[v] == dfn[u]) {
				vcc++;
				bl[v] = vcc;
				int cnt = 0;
				while(stk[top - 1] != u) {
					cnt++;
					top--;
					to[stk[top]].emplace_back(n + vcc);
					to[n + vcc].emplace_back(stk[top]);
				}
				if(cnt == 1) val[vcc] = -INF;
				to[u].emplace_back(n + vcc), to[n + vcc].emplace_back(u);
			}
		}
	}
}

int vis[N];
void tarjan2(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v]) {
			if(dfn[v] < dfn[u] && v != ff[u]) {
				// printf("> %d (u=%d,v=%d,return)\n", bl[u], u, v);
				val[bl[u]]++;
			}
		} else {
			if(!bl[v]) bl[v] = bl[u];
			// printf("> %d (u=%d,v=%d,son)\n", bl[v], u, v);
			val[bl[v]]++;
			tarjan2(v);
		}
	}
}

int sum[2 * N];
int dep[2 * N], go[21][2 * N];
void dfs(int u) {
	dep[u] = dep[go[0][u]] + 1;
	sum[u] = sum[go[0][u]] + (u <= n ? 0 : val[u - n]);
	for(int v : to[u]) if(v != go[0][u]) go[0][v] = u, dfs(v);
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = go[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(go[i][u] != go[i][v]) u = go[i][u], v = go[i][v];
	return go[0][u];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	tarjan(1), tarjan2(1);
	for(int i = 1; i <= vcc; i++) val[i] = std::max(val[i], 0);
	// for(int i = 1; i <= n; i++) printf("bl[%d] = %d\n", i, bl[i]);
	dfs(1), binary_lifting();
	// for(int i = 1; i <= n + vcc; i++) printf("val[%d] = %d, sum[%d] = %d\n", i, val[i], i, sum[i]);
	scanf("%d", &Q);
	while(Q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int l = lca(u, v);
		// printf("l = %d\n", l);
		printf("%d\n", sum[u] + sum[v] - sum[l] - sum[go[0][l]]);
	}
	return 0;
}