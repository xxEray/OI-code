#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int LOGN = 22;
const int INF = 0x3f3f3f3f;

int n, m, K;

int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::vector<int> vct[N];
int fa[21][N], dep[N], dfn[N], time_stamp;
void dfs(int u) {
	dfn[u] = ++time_stamp;
	dep[u] = dep[fa[0][u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[0][u]) {
		int v = edge[i].to;
		fa[0][v] = u;
		dfs(v);
	}
}
void binary_lifting() {
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= n; i++)
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v]) >> i & 1) u = fa[i][u];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--) if(fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

std::vector<int> to[N * LOGN];
void link(int cl, int u, int v) {
	assert(dep[u] > dep[v]);
	for(int i = 0; i <= 20; i++) if((dep[u] - dep[v] + 1) >> i & 1) to[cl].push_back((i == 0 ? 0 : i + 1) * n + u), u = fa[i][u];
}

int vis[N * LOGN], dfn2[N * LOGN], low[N * LOGN], sz[N * LOGN], stk[N * LOGN], bl[N * LOGN];
int scc, time_stamp2, top;
void tarjan(int u) {
	low[u] = dfn2[u] = ++time_stamp2;
	stk[top++] = u;
	vis[u] = 1;
	for(int v : to[u])
		if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
		else if(!vis[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
	if(low[u] == dfn2[u]) {
		scc++;
		do {
			top--;
			bl[stk[top]] = scc;
			sz[scc] += (n + 1 <= stk[top] && stk[top] <= n + K);
			vis[stk[top]] = 2;
		} while(stk[top] != u);
	}
}

bool oud[N * LOGN];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1);
	binary_lifting();
	for(int i = 1; i <= n; i++) to[i].push_back(n + a[i]), to[n + a[i]].push_back(i), vct[a[i]].push_back(i);
	for(int j = 1; j <= 20; j++) for(int i = 1; i <= n; i++) {
		to[(j + 1) * n + i].push_back((j == 1 ? 0 : j) * n + i);
		if(fa[j - 1][i]) to[(j + 1) * n + i].push_back((j == 1 ? 0 : j) * n + fa[j - 1][i]);
	}
	for(int i = 1; i <= K; i++) {
		std::sort(vct[i].begin(), vct[i].end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
		std::vector<int> tmp = vct[i];
		for(int j = 0; j < (int)vct[i].size() - 1; j++) tmp.push_back(lca(vct[i][j], vct[i][j + 1]));
		std::sort(tmp.begin(), tmp.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
		tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
		// if(i == 2) { printf("tmp: "); for(int x : tmp) printf("%d ", x); puts(""); }
		for(int j = 0; j < (int)tmp.size() - 1; j++) {
			int l = lca(tmp[j], tmp[j + 1]);
			link(i + n, tmp[j + 1], l);
		}
	}
	m = 22 * n;
	// for(int i = 1; i <= m; i++) for(int j : to[i]) printf("%d -> %d\n", i, j);
	for(int i = 1; i <= m; i++) if(!vis[i]) tarjan(i);
	for(int u = 1; u <= m; u++) for(int v : to[u]) if(bl[u] != bl[v]) oud[bl[u]] = true;
	int ans = INF;
	for(int i = 1; i <= scc; i++) if(!oud[i] && sz[i]) {
		ans = std::min(ans, sz[i]);
		// printf("scc = %d, sz = %d: ", i, sz[i]);
		// for(int j = 1; j <= m; j++) if(bl[j] == i) printf("%d ", j);
		// puts("");
	}
	printf("%d\n", ans - 1);
	return 0;
}