#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const int M = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, src, dst;
LL w[N], a[N], b[N];
struct Edge { int to, nxt; LL w; } edge[M << 1];
int head[N];
void add_edge(int u, int v, LL ww) { static int k = 1; edge[k] = (Edge){v, head[u], ww}, head[u] = k++; }

bool vis[N];
void dijkstra(int st, LL *dis) {
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<std::pair<LL, int>>> q;
	for(int i = 1; i <= n; i++) dis[i] = LLINF, vis[i] = false;
	dis[st] = 0, q.push({dis[st], st});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(dis[v] < dis[u] + edge[i].w) continue;
			dis[v] = dis[u] + edge[i].w;
			q.push({dis[v], v});
		}
	}
}

LL tmp[N];
void discrete(LL *arr) {
	for(int i = 1; i <= n; i++) tmp[i] = arr[i];
	std::sort(tmp + 1, tmp + n + 1);
	int c = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) arr[i] = std::lower_bound(tmp + 1, tmp + c + 1, arr[i]) - tmp;
}

LL f[2][N][N], g[2][N][N];
int h[2][N][N];

int main() {
	scanf("%d%d%d%d", &n, &m, &src, &dst);
	for(int i = 1; i <= n; i++) scanf("%lld", &w[i]);
	for(int i = 1; i <= m; i++) { int u, v; LL ww; scanf("%d%d%lld", &u, &v, &ww); add_edge(u, v, ww), add_edge(v, u, ww); }
	dijkstra(src, a), dijkstra(dst, b);
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%lld ", a[i]); puts("");
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%lld ", b[i]); puts("");
	discrete(a), discrete(b);
	// for(int i = 1; i <= n; i++) printf("%d: w=%lld, a=%lld, b=%lld\n", i, w[i], a[i], b[i]);
	for(int i = 1; i <= n; i++) g[0][a[i]][b[i] - 1] += w[i], g[1][a[i] - 1][b[i]] += w[i];
	for(int i = 1; i <= n; i++) h[0][a[i]][b[i] - 1]++, h[1][a[i] - 1][b[i]]++;
	for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--) g[0][i][j] += g[0][i][j + 1], g[1][i][j] += g[1][i + 1][j];
	for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--) h[0][i][j] += h[0][i][j + 1], h[1][i][j] += h[1][i + 1][j];
	for(int i = 0; i <= n; i++) f[0][i][n] = f[0][n][i] = f[1][i][n] = f[1][n][i] = 0;
	for(int i = n - 1; i >= 0; i--) for(int j = n - 1; j >= 0; j--) {
		f[0][i][j] = std::max(f[0][i + 1][j], (h[0][i + 1][j] ? f[1][i + 1][j] : -LLINF)) + g[0][i + 1][j];
		f[1][i][j] = std::min(f[1][i][j + 1], (h[1][i][j + 1] ? f[0][i][j + 1] : LLINF)) - g[1][i][j + 1];
	}
	// for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--) printf("g[%d][%d] = %lld,%lld\n", i, j, g[0][i][j], g[1][i][j]);
	// for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--) printf("f[%d][%d] = %lld,%lld\n", i, j, f[0][i][j], f[1][i][j]);
	puts(f[0][0][0] > 0 ? "Break a heart" : (f[0][0][0] < 0 ? "Cry" : "Flowers"));
	return 0;
}