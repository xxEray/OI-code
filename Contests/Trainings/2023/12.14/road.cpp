#include <bits/stdc++.h>

typedef long long LL;

const int N = 300 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, K;

LL self[N], c[N][N], e[N][N], dis[N][N];
LL mx[N];

int main() {
#ifndef DEBUG
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = (i == j ? 0 : LLINF);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) c[i][j] = -LLINF;
	for(int i = 1; i <= n; i++) self[i] = LLINF;
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(u != v) e[u][v] = e[v][u] = w;
		else self[u] = w;
	}
	scanf("%d", &K);
	while(K--) { int u, v, w; scanf("%d%d%d", &u, &v, &w); c[u][v] = c[v][u] = w; }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = e[i][j];
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	int ans = 0;
	for(int p = 1; p <= n; p++) {
		for(int j = 1; j <= n; j++) mx[j] = -LLINF;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) mx[j] = std::max(mx[j], c[i][j] - dis[i][p]);
		for(int q = 1; q <= n; q++) if(p != q) {
			LL mxv = 0;
			for(int j = 1; j <= n; j++) mxv = std::max(mxv, mx[j] - dis[j][q]);
			ans += (mxv >= e[p][q]);
		}
	}
	ans /= 2;
	for(int p = 1; p <= n; p++) if(self[p] < LLINF) {
		bool flag = false;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) flag |= (dis[i][p] + self[p] + dis[p][j] <= c[i][j]);
		ans += flag;
	}
	printf("%d\n", ans);
	return 0;
}