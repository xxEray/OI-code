#include <cstdio>
#include <algorithm>

#define int long long

const int N = 1e5 + 5;
const int MAXK = 20 + 3;

int n, m, K;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int ans;
int cnt[N][MAXK], val[N][MAXK];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		for(int j = 1; j <= K; j++) cnt[u][j] += cnt[v][j - 1];
		for(int j = 0; j < K; j++) val[u][j] += val[v][j + 1];
	}
	cnt[u][0] = 1;
	for(int j = 0; j < K; j++) {
		int v = std::min(cnt[u][j], val[u][j]);
		cnt[u][j] -= v, val[u][j] -= v;
		v = std::min(cnt[u][j - 1], val[u][j]);
		cnt[u][j - 1] -= v, val[u][j] -= v;
	}
	if(cnt[u][K]) {
		int t = (cnt[u][K] + m - 1) / m;
		val[u][K] = t * m - cnt[u][K], cnt[u][K] = 0, ans += t;
	}
	int v = std::min(val[u][K], cnt[u][K - 1]);
	val[u][K] -= v, cnt[u][K - 1] -= v;
}

signed main() {
#ifndef DEBUG
	freopen("scattered.in", "r", stdin);
	freopen("scattered.out", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &K);
	for(int i = 1; i < n; i++) { int u, v; scanf("%lld%lld", &u, &v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	int sum = 0;
	for(int i = K; i >= 0; i--) {
		sum += val[1][i];
		int t = cnt[1][i] <= sum ? 0 : (cnt[1][i] - sum + m - 1) / m;
		ans += t, sum += t * m;
		sum -= cnt[1][i];
	}
	printf("%lld\n", ans);
	return 0;
} /*
10 10 2
1 8
2 3
1 5
2 4
1 2
8 9
8 10
5 6
5 7

*/