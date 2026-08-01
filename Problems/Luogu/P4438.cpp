#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 40000 + 5;
const int ROAD = 40 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
int son[N][2], fa[N];
LL a[N], b[N], c[N];

LL f[100][ROAD][ROAD], g[100][ROAD][ROAD];

void dfs(int u, int t) {
	if(u >= n) {
		for(int i = 0; i <= 41; i++) f[t][i][41] = f[t][41][i] = LLINF;
		for(int i = 0; i <= 40; i++) for(int j = 0; j <= 40; j++)
			f[t][i][j] = c[u] * (a[u] + i) * (b[u] + j);
		return;
	}
	dfs(son[u][0], t + 1);
	for(int i = 0; i <= 41; i++) for(int j = 0; j <= 41; j++) g[t][i][j] = f[t + 1][i][j];
	dfs(son[u][1], t + 1);
	for(int i = 0; i <= 40; i++) for(int j = 0; j <= 40; j++)
		f[t][i][j] = std::min(g[t][i][j] + f[t + 1][i][j + 1], g[t][i + 1][j] + f[t + 1][i][j]);
	for(int i = 0; i <= 41; i++) f[t][i][41] = f[t][41][i] = LLINF;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u < 0) u = -u + n - 1;
		if(v < 0) v = -v + n - 1;
		fa[u] = fa[v] = i, son[i][0] = u, son[i][1] = v;
	}
	for(int i = n; i <= 2 * n - 1; i++) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	dfs(1, 1);
	printf("%lld\n", f[1][0][0]);
	return 0;
}