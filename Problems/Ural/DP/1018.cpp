#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) {
	static int k = 1;
	edge[k] = (Edge){v, head[u], w};
	head[u] = k++;
}

int n, m;

int sum[N], f[N][N];

void dfs(int u, int fa) {
	int ls = 0, rs = 0, wl, wr;
	for(int i = head[u]; i; i = edge[i].nxt)
		if(edge[i].to != fa) {
			if(ls) rs = edge[i].to, wr = edge[i].w;
			else ls = edge[i].to, wl = edge[i].w;
		}
	if(ls) dfs(ls, u), sum[u] += sum[ls] + 1;
	if(rs) dfs(rs, u), sum[u] += sum[rs] + 1;
	printf("%d: sum = %d, ls = %d, rs = %d\n", u, sum[u], ls, rs);
	for(int i = 0; i <= m; i++) {
		if(ls)
			for(int j = 1; j <= std::min(sum[rs] + 1, i); j++)
				f[u][i] = std::max(f[u][i], f[ls][i - j] + wl);
		if(rs)
			for(int j = 1; j <= std::min(sum[ls] + 1, i); j++)
				f[u][i] = std::max(f[u][i], f[rs][i - j] + wr);
		if(ls && rs)
			for(int j = 0; j <= i; j++)
				f[u][i] = std::max(f[u][i], f[ls][j] + f[rs][i - j] + wl + wr);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			f[i][j] = -INF;
	dfs(1, 0);
	printf("%d\n", f[1][m]);
	return 0;
}