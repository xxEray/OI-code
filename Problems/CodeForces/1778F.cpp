#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++;  }

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
int lcm[1005][1005];

std::vector<int> vals[1005];
int f[N][1005];
bool exist[1005];
int tmp[1005];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u);
	for(int j : vals[a[1]]) tmp[j] = 0;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) for(int j : vals[a[1]]) tmp[j] += f[edge[i].to][j], tmp[j] = std::min(tmp[j], INF);
	for(int j : vals[a[1]])
		if(j <= a[u] * a[u] && a[u] * a[u] % j == 0) {
			if(j <= a[u] && a[u] % j == 0) f[u][j] = tmp[j];
			else f[u][j] = INF;
			for(int k : vals[a[1]]) if(j % k == 0 && exist[lcm[k][j / k]])
				f[u][j] = std::min(f[u][j], tmp[lcm[k][j / k]] + 1);
		} else f[u][j] = INF;
}

int main() {
	int T; scanf("%d", &T);
	for(int i = 1; i <= 1000; i++) for(int j = 1; j <= i; j++) if(i % j == 0) vals[i].push_back(j);
	for(int i = 1; i <= 1000; i++) for(int j = 1; j <= 1000; j++) lcm[i][j] = i / gcd(i, j) * j;
	while(T--) {
		ek = 1;
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) head[i] = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= 1000; j++) f[i][j] = 0;
		for(int j = 1; j <= 1000; j++) exist[j] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
		for(int i : vals[a[1]]) exist[i] = 1;
		dfs(1, 0);
		// for(int i = 1; i <= n; i++) for(int j : vals[a[1]]) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
		for(int j : vals[a[1]]) tmp[j] = 0;
		for(int i = head[1]; i; i = edge[i].nxt) for(int j : vals[a[1]]) tmp[j] += f[edge[i].to][j], tmp[j] = std::min(tmp[j], INF);
		int ans = a[1];
		for(int j : vals[a[1]]) if(tmp[j] <= K - 1) ans = std::max(ans, a[1] * j);
		printf("%d\n", ans);
	}
	return 0;
}