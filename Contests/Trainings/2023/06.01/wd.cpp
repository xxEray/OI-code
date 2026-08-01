#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int MAXD = 50 + 5;
const int INF = 0x3f3f3f3f;

int n, m, D;
bool a[N][MAXD];
struct Edge { int to, nxt; } edge[N];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int dfn[N], low[N], bl[N], vis[N];
int stk[N], top, time_stamp, scc;
int last[N], nxt[N];
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}

inline int hash(int u, int t) { return (u - 1) * D + t; }

int w[N][MAXD];
Edge edge2[N * MAXD];
int head2[N * MAXD];
void add_edge2(int u, int v) { static int k = 1; edge2[k] = (Edge){v, head2[u]}, head2[u] = k++; }
Edge edge3[N * MAXD];
int head3[N * MAXD];
void add_edge3(int u, int v) { static int k = 1; edge3[k] = (Edge){v, head3[u]}, head3[u] = k++; }
bool reach[N * MAXD], reachr[N * MAXD];
bool dis[N][MAXD], disr[N][MAXD];
int q[N * MAXD];
void calc(int id) {
	for(int u = last[id]; u; u = nxt[u])
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(bl[v] == id) for(int j = 0; j < D; j++) add_edge2(hash(u, j), hash(v, (j + 1) % D)), add_edge3(hash(v, j), hash(u, (j + 1) % D));
		}
	int hd = 0, tl = 0;
	reach[hash(last[id], 0)] = true, q[tl++] = hash(last[id], 0);
	while(hd < tl) {
		int u = q[hd++];
		for(int i = head2[u]; i; i = edge2[i].nxt) {
			int v = edge2[i].to;
			if(reach[v]) continue;
			reach[v] = true;
			q[tl++] = v;
		}
	}
	for(int u = last[id]; u; u = nxt[u]) for(int i = 0; i < D; i++) if(reach[hash(u, i)]) dis[u][i] = true;
	hd = 0, tl = 0;
	reachr[hash(last[id], 0)] = true, q[tl++] = hash(last[id], 0);
	while(hd < tl) {
		int u = q[hd++];
		for(int i = head3[u]; i; i = edge3[i].nxt) {
			int v = edge3[i].to;
			if(reachr[v]) continue;
			reachr[v] = true;
			q[tl++] = v;
		}
	}
	for(int u = last[id]; u; u = nxt[u]) for(int i = 0; i < D; i++) if(reachr[hash(u, i)]) disr[u][i] = true;
	for(int u = last[id]; u; u = nxt[u]) for(int i = 0; i < D; i++) {
		bool ok = false;
		for(int j = 0; j < D; j++) ok |= (a[u][(i + j) % D] && dis[u][j]);
		w[id][i] += ok;
	}
}

std::vector<std::pair<int, int>> edges[N];

int f[N][MAXD];
bool tmp[MAXD];
void getf(int id) {
	if(vis[id]) return;
	vis[id] = 1;
	for(auto &e : edges[id]) {
		int u = e.first, v = e.second;
		getf(bl[u]);
		for(int i = 0; i < D; i++) tmp[i] = false;
		for(int i = 0; i < D; i++) for(int j = 0; j < D; j++) if(dis[u][i] && disr[v][j]) tmp[(i + j + 1) % D] = true;
		for(int i = 0; i < D; i++) for(int j = 0; j < D; j++) if(tmp[j]) f[id][i] = std::max(f[id][i], f[bl[u]][(i - j + D) % D] + w[id][i]);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &D);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v); }
	for(int i = 1; i <= n; i++) {
		char str[MAXD];
		scanf("%s", str);
		for(int j = 0; j < D; j++) a[i][j] = str[j] - '0';
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	for(int i = n; i >= 1; i--) nxt[i] = last[bl[i]], last[bl[i]] = i;
	// fprintf(stderr, "calc start, time = %d\n", (int)clock());
	for(int i = 1; i <= scc; i++) calc(i); // , fprintf(stderr, "calc %d done, time = %d\n", i, (int)clock());
	// fprintf(stderr, "calc done, time = %d\n", (int)clock());
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: bl = %d, represent = %d, dis = ", i, bl[i], last[bl[i]]);
	// 	for(int j = 0; j < D; j++) printf("%d", dis[i][j]);
	// 	printf(", disr = ");
	// 	for(int j = 0; j < D; j++) printf("%d", disr[i][j]);
	// 	puts("");
	// }
	// for(int i = 1; i <= scc; i++) {
	// 	printf("scc %d: w=", i);
	// 	for(int j = 0; j < D; j++) printf("%d ", w[i][j]);
	// 	puts("");
	// }
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(bl[u] != bl[v]) edges[bl[v]].push_back({u, v});
	}
	int ans = 0;
	for(int i = 1; i <= scc; i++) vis[i] = 0;
	for(int i = 1; i <= scc; i++) for(int j = 0; j < D; j++) f[i][j] = -INF;
	for(int i = 0; i < D; i++) if(disr[1][i]) f[bl[1]][i] = std::max(f[bl[1]][i], w[bl[1]][i]);
	for(int i = 1; i <= scc; i++) getf(i);
	// for(int i = 1; i <= scc; i++) for(int j = 0; j < D; j++) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	for(int i = 1; i <= scc; i++) for(int j = 0; j < D; j++) ans = std::max(ans, f[i][j]);
	printf("%d\n", ans);
	// fprintf(stderr, "time = %d\n", (int)clock());
	return 0;
} /*
4 5 3
3 1
1 2
2 4
4 1
2 3
011
110
111
001
*/