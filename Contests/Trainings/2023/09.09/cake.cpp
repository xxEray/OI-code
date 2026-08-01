#include <bits/stdc++.h>

#define y1 y41235213

const int N = 14 + 5;
const int MAXS = (1 << 14) + 5;
const int HALFS = (1 << 7) + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N][N];

int sum(int x1, int y1, int x2, int y2) { return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1]; }

int fu[HALFS][MAXS], fd[HALFS][MAXS], g[N][N][MAXS], hu[HALFS], hd[HALFS];

int ans[N][N];

int main() {
// #ifndef DEBUG
	freopen("cake.in", "r", stdin);
	freopen("cake.out", "w", stdout);
// #endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] += a[i - 1][j];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] += a[i][j - 1];
	int Um = (1 << (m - 1)) - 1, Uu = (1 << ((n - 1) / 2)) - 1, Ud = (1 << (n / 2)) - 1;
	for(int s = 0; s <= Uu; s++) for(int t = 0; t <= Um; t++) {
		fu[s][t] = INF;
		for(int i0 = 1, i = 1; i <= (n - 1) / 2; i++) if(s >> (i - 1) & 1) {
			for(int j0 = 1, j = 1; j <= m; j++) if(j == m || (t >> (j - 1) & 1)) {
				fu[s][t] = std::min(fu[s][t], sum(i0, j0, i, j));
				j0 = j + 1;
			}
			i0 = i + 1;
		}
	}
	for(int s = 0; s <= Ud; s++) for(int t = 0; t <= Um; t++) {
		fd[s][t] = INF;
		for(int i0 = n, i = n - 1; i > (n - 1) / 2; i--) if(s >> (i - (n - 1) / 2 - 1) & 1) {
			for(int j0 = 1, j = 1; j <= m; j++) if(j == m || (t >> (j - 1) & 1)) {
				fd[s][t] = std::min(fd[s][t], sum(i + 1, j0, i0, j));
				j0 = j + 1;
			}
			i0 = i;
		}
	}
	for(int s = 0; s <= Uu; s++) {
		int mx = 0;
		for(int i = 1; i <= (n - 1) / 2; i++) if(s >> (i - 1) & 1) mx = std::max(mx, i);
		hu[s] = mx + 1;
	}
	for(int s = 0; s <= Ud; s++) {
		int mn = n;
		for(int i = n - 1; i > (n - 1) / 2; i--) if(s >> (i - (n - 1) / 2 - 1) & 1) mn = std::min(mn, i);
		hd[s] = mn;
	}
	for(int i = 1; i <= (n - 1) / 2 + 1; i++) for(int j = n; j >= (n - 1) / 2 + 1; j--) for(int t = 0; t <= Um; t++) {
		g[i][j][t] = INF;
		for(int k = 1, k0 = 1; k <= m; k++) if(k == m || (t >> (k - 1) & 1)) {
			g[i][j][t] = std::min(g[i][j][t], sum(i, k0, j, k));
			k0 = k + 1;
		}
	}
	for(int su = 0; su <= Uu; su++) for(int sd = 0; sd <= Ud; sd++) {
		int s = (su | (sd << ((n - 1) / 2)));
		int szs = __builtin_popcount(s);
		for(int t = 0; t <= Um; t++) {
			int szt = __builtin_popcount(t);
			ans[szs][szt] = std::max(ans[szs][szt], std::min({fu[su][t], fd[sd][t], g[hu[su]][hd[sd]][t]}));
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) printf("%d ", ans[i][j]);
		puts("");
	}
	return 0;
} /*
3 4
1 2 3 4
5 3 2 1
6 3 4 2
*/