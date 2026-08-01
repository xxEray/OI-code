#include <bits/stdc++.h>

const int N = 500 + 5;
const int MAXQ = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N], b[N], w[N][N];

std::vector<std::array<int, 3>> qr[N][N];
int out[MAXQ];

int f[N][N], g[N][N], h1[N][N], h2[N][N];

int main() {
#ifndef DEBUG
	freopen("ape.in", "r", stdin);
	freopen("ape.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &w[i][j]);
	for(int i = 1; i <= Q; i++) {
		int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		qr[l1][l2].push_back({r1, r2, i});
	}
	for(int p = 1; p <= n; p++) for(int q = 1; q <= n; q++) {
		// printf("p = %d, q = %d\n", p, q);
		for(int i = p - 1; i <= n; i++) f[i][q - 1] = h1[i][q - 1] = h2[i][q - 1] = -INF, g[i][q - 1] = 0;
		for(int i = q; i <= n; i++) f[p - 1][i] = h1[p - 1][i] = h2[p - 1][i] = -INF, g[p - 1][i] = 0;
		for(int i = p; i <= n; i++) for(int j = q; j <= n; j++) {
			f[i][j] = std::max({h2[i][j - 1] + w[i][j] - b[j], h1[i - 1][j] + w[i][j] - a[i], g[i - 1][j - 1] + w[i][j] - a[i] - b[j]});
			h1[i][j] = std::max(f[i][j], h1[i - 1][j]);
			h2[i][j] = std::max(f[i][j], h2[i][j - 1]);
			g[i][j] = std::max({f[i][j], g[i - 1][j], g[i][j - 1]});
			// printf("[%d][%d]: f=%d, g=%d\n", i, j, f[i][j], g[i][j]);
		}
		for(auto [i, j, id] : qr[p][q]) out[id] = g[i][j];
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i]);
	return 0;
}