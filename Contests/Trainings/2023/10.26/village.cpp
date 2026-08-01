#include <bits/stdc++.h>

const int N = 300 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N][N];

int lim[N][N][N];

int mnx, mny, mxx, mxy;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[N][N];
void dfs(int x, int y) {
	vis[x][y] = true;
	mnx = std::min(mnx, x), mxx = std::max(mxx, x);
	mny = std::min(mny, y), mxy = std::max(mxy, y);
	for(int i = 0; i < 4; i++) {
		int dx = x + dir[i][0], dy = y + dir[i][1];
		if(1 <= dx && dx <= n && 1 <= dy && dy <= m && a[dx][dy] == 0 && !vis[dx][dy]) dfs(dx, dy);
	}
}

int dot[N], face[N], vedge[N], hedge[N];

int buff[500005], *tin;

int main() {
#ifndef DEBUG
	freopen("village.in", "r", stdin);
	freopen("village.out", "w", stdout);
#endif
	tin = buff + 250000;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
	for(int u = 1; u <= n + 1; u++) for(int d = u - 1; d <= n; d++) for(int i = 1; i <= m + 1; i++) lim[u][d][i] = m;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!vis[i][j] && a[i][j] == 0) {
		mnx = mny = INF, mxx = mxy = -INF;
		dfs(i, j);
		// printf("mnx = %d, mxx = %d, mny = %d, mxy = %d\n", mnx, mxx, mny, mxy);
		lim[mnx - 1][mxx + 1][mny - 1] = std::min(lim[mnx - 1][mxx + 1][mny - 1], mxy);
	}
	for(int u = n; u >= 1; u--) for(int d = u; d <= n; d++) for(int l = m; l >= 1; l--) lim[u][d][l] = std::min({lim[u][d][l], lim[u + 1][d][l], lim[u][d - 1][l], lim[u][d][l + 1]});
	long long ans = 0;
	for(int u = 1; u <= n; u++) {
		for(int i = 1; i <= m; i++) dot[i] = face[i] = vedge[i] = hedge[i] = 0;
		for(int d = u; d <= n; d++) {
			int sum = 0;
			for(int i = 1; i <= m; i++) sum += (a[d][i] == 1), dot[i] += sum;
			sum = 0;
			for(int i = 2; i <= m; i++) sum += (a[d][i - 1] && a[d][i]), hedge[i] += sum;
			if(d > u) {
				sum = 0;
				for(int i = 1; i <= m; i++) sum += (a[d - 1][i] && a[d][i]), vedge[i] += sum;
				sum = 0;
				for(int i = 2; i <= m; i++) sum += (a[d - 1][i - 1] && a[d - 1][i] && a[d][i - 1] && a[d][i]), face[i] += sum;
			}
			int r = m;
			// std::vector<std::array<int, 4>> output;
			for(int l = m; l >= 1; l--) {
				// (dot[r] + face[r] - vedge[r] - hedge[r]) - (dot[l - 1] + face[l] - vedge[l - 1] - hedge[l]) == 1
				tin[dot[l] + face[l] - vedge[l] - hedge[l]]++;
				while(r > lim[u][d][l]) tin[dot[r] + face[r] - vedge[r] - hedge[r]]--, r--;
				// if(tin[dot[l - 1] + face[l] - vedge[l - 1] - hedge[l] + 1]) output.push_back({u, d, l, tin[dot[l - 1] + face[l] - vedge[l - 1] - hedge[l] + 1]});
				ans += tin[dot[l - 1] + face[l] - vedge[l - 1] - hedge[l] + 1];
			}
			// std::reverse(output.begin(), output.end());
			// for(const auto &[x, y, z, v] : output) printf("%d %d %d %d\n", x, y, z, v);
			while(r >= 1) tin[dot[r] + face[r] - vedge[r] - hedge[r]]--, r--;
			// for(int i = 0; i <= n * m; i++) assert(tin[i] == 0);
		}
	}
	printf("%lld\n", ans);
	return 0;
} /*
4 4
1111
1101
1001
1111
*/