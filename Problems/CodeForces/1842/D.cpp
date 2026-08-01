#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL dis[N][N];

LL ans[N], total;

LL val[N], tmp[N];
int c;
void discrete() {
	c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = ans[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		LL vv = ans[i];
		ans[i] = std::lower_bound(tmp + 1, tmp + c + 1, ans[i]) - tmp;
		val[ans[i]] = vv;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : LLINF);
	for(int i = 1; i <= m; i++) { int u, v; LL w; scanf("%d%d%lld", &u, &v, &w); dis[u][v] = dis[v][u] = std::min(dis[u][v], w); }
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	total = dis[1][n];
	if(total == LLINF) { puts("inf"); return 0; }
	assert(total <= 1000000000000000000);
	ans[1] = total, ans[n] = 0;
	for(int i = 2; i <= n - 1; i++) ans[i] = std::max(total - dis[1][i], 0LL);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) assert(dis[i][j] >= std::abs(ans[i] - ans[j]));
	discrete();
	assert(c <= n * n);
	printf("%lld %d\n", total, c - 1);
	for(int i = 2; i <= c; i++) {
		for(int j = 1; j <= n; j++) printf("%d", ans[j] >= i ? 1 : 0);
		printf(" %lld\n", val[i] - val[i - 1]);
	}
	return 0;
} /*
4 4
1 3 1
3 4 10
1 2 1
2 3 1
*/