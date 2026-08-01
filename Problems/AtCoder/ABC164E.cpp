#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 50 + 5;
const int M = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Cost { LL coin, time; };
struct Edge { int to, nxt; Cost w; } edge[M << 1];
int head[N];
void add_edge(int u, int v, Cost w) {
	static int k = 1;
	edge[k] = (Edge){v, head[u], w};
	head[u] = k++;
}
Cost a[N];
int n, m;

// f[i][j][k] 表示走到第 i 个城市，剩余 j(<=50N) 个银币的最小时间
LL f[N][N * N];
int mxw;

void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			int v = edge[i].to;
			for(int j = (int)edge[i].w.coin; j <= mxw; j++)
				for(int k = 0; k <= mxw; k += a[v].coin)
					f[v][j - (int)edge[i].w.coin + k] = std::min(f[v][j - (int)edge[i].w.coin + k], f[u][j] + edge[i].w.time + k / a[v].coin * a[v].time);
			dfs(v, u);
		}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		Cost w;
		scanf("%d%d%lld%lld", &u, &v, &w.coin, &w.time);
		add_edge(u, v, w);
		add_edge(v, u, w);
		mxw = std::max(mxw, (int)w.coin);
	}
	for(int i = 1; i <= n; i++) {
		Cost w;
		scanf("%lld%lld", &w.coin, &w.time);
		a[i] = w;
	}
	mxw *= n;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= mxw; j++)
			f[i][j] = LLINF;
	for(int w = 0; w <= mxw; w += a[1].coin) f[1][w] = w / a[1].coin * a[1].time;
	dfs(1, 0);
	printf("   ");
	for(int i = 0; i <= mxw; i++) printf("%2d ", i);
	puts("");
	for(int i = 1; i <= n; i++) {
		printf("%d: ", i);
		for(int j = 0; j <= mxw; j++) printf("%2lld ", f[i][j] == LLINF ? -1 : f[i][j]);
		puts("");
	}
	for(int i = 2; i <= n; i++) {
		LL ans = LLINF;
		for(int j = 0; j <= mxw; j++)
			ans = std::min(ans, f[i][j]);
		printf("%lld\n", ans);
	}
	return 0;
}