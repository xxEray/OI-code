#include <bits/stdc++.h>

typedef long long LL;

const int N4 = 20 + 3;
const int N = 75 + 2;
const int M = 300 + 5;
const int MAXS = (1 << 18) + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, K;
LL A, B;
struct Edge { int to, nxt, w; } edge[M << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

int color[N], cnt;
int color2[N], cnt2;
int sz[N];
LL f[MAXS][N], g[N];

bool vis[N];
std::vector<int> vct;
void dfs(int u) {
	if(vis[u]) return;
	vis[u] = true;
	vct.emplace_back(u);
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].w == A) dfs(edge[i].to);
}

LL disi[N][N], diso[N][N];
LL e[N][N], e2[N][N];
std::vector<int> to[N];

int main() {
	// freopen("pink.in", "r", stdin);
	// freopen("pink.out", "w", stdout);
	scanf("%d%d%lld%lld", &n, &m, &A, &B);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		vct.clear();
		dfs(i);
		cnt2++;
		for(int u : vct) color2[u] = cnt2;
		if(vct.size() >= 4) {
			cnt++;
			sz[cnt] = vct.size();
			for(int u : vct) color[u] = cnt;
		}
	}
	// for(int i = 1; i <= n; i++) printf("color[%d] = %d %d\n", i, color[i], color2[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) disi[i][j] = diso[i][j] = (i == j ? 0 : LLINF);
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(color[u] && color[v] && color[u] == color[v] && edge[i].w == A) disi[u][v] = edge[i].w;
		if(!color[u] && !color[v] && (color2[u] != color2[v] || edge[i].w == A)) diso[u][v] = std::min(diso[u][v], (LL)edge[i].w);
	}
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) disi[i][j] = std::min(disi[i][j], disi[i][k] + disi[k][j]);
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) diso[i][j] = std::min(diso[i][j], diso[i][k] + diso[k][j]);
	for(int u = 1; u <= n; u++) for(int v = 1; v <= n; v++) e[u][v] = e2[u][v] = LLINF;
	for(int u = 1; u <= n; u++) for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(color[u] && color[v] && color[u] != color[v]) e[u][v] = std::min(e[u][v], (LL)edge[i].w);
	}
	for(int u = 1; u <= n; u++) if(color[u]) for(int v = 1; v <= n; v++) if(color[v] && color[u] != color[v])
		for(int i = head[u]; i; i = edge[i].nxt) if(!color[edge[i].to])
			for(int j = head[v]; j; j = edge[j].nxt) if(!color[edge[j].to])
				e[u][v] = std::min(e[u][v], edge[i].w + edge[j].w + diso[edge[i].to][edge[j].to]);
	for(int u = 1; u <= n; u++) if(color[u])
		for(int v = 1; v <= n; v++) if(color[v] && color[v] != color[u])
			for(int t = 1; t <= n; t++) if(color[t] == color[v])
				e2[u][t] = std::min(e2[u][t], e[u][v] + disi[v][t]);
	// for(int u = 1; u <= n; u++) for(int v = u + 1; v <= n; v++)
	// 	if(disi[u][v] <= LLINF / 2 || diso[u][v] <= LLINF / 2)
	// 		printf("dis[%d][%d] = %lld,%lld\n", u, v, disi[u][v], diso[u][v]);
	for(int u = 1; u <= n; u++) for(int v = 1; v <= n; v++) if(e2[u][v] <= LLINF / 2) to[u].emplace_back(v);
	int U = (1 << cnt) - 1;
	for(int s = 0; s <= U; s++) for(int u = 1; u <= n; u++) f[s][u] = LLINF;
	if(color[1]) {
		for(int u = 1; u <= n; u++) if(color[u] == color[1]) f[1 << (color[u] - 1)][u] = disi[1][u];
	} else {
		for(int u = 1; u <= n; u++) if(color[u])
			for(int v = 1; v <= n; v++) if(color[v] == color[u])
				for(int i = head[v]; i; i = edge[i].nxt) if(!color[edge[i].to])
					f[1 << (color[u] - 1)][u] = std::min(f[1 << (color[u] - 1)][u], disi[u][v] + edge[i].w + diso[edge[i].to][1]);
	}
	for(int s = 0; s <= U; s++) for(int u = 1; u <= n; u++)
		if(color[u] && (s >> (color[u] - 1) & 1) && f[s][u] <= LLINF / 2) {
			for(int v : to[u]) if(~s >> (color[v] - 1) & 1)
				f[s | (1 << (color[v] - 1))][v] = std::min(f[s | (1 << (color[v] - 1))][v], f[s][u] + e2[u][v]);
		}
	for(int i = 1; i <= n; i++) g[i] = LLINF;
	for(int s = 0; s <= U; s++) for(int u = 1; u <= n; u++) g[u] = std::min(g[u], f[s][u]);
	for(int u = 1; u <= n; u++)
		if(color[u]) printf("%lld ", g[u]);
		else {
			LL ans = diso[1][u];
			for(int v = 1; v <= n; v++) if(!color[v])
				for(int i = head[v]; i; i = edge[i].nxt) if(color[edge[i].to])
					ans = std::min(ans, diso[u][v] + edge[i].w + g[edge[i].to]);
			printf("%lld ", ans);
		}
	puts("");
	return 0;
}