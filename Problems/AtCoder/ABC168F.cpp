#include <cstdio>
#include <algorithm>
#include <queue>

#define int long long

typedef long long LL;

const int N = 1000 + 5;
// const LL INF = 4e18 + 5;

struct Row { int x, sty, edy; } r[N];
struct Column { int stx, edx, y; } c[N];

int n, m, h, w;

int zerox, zeroy;
LL subx[N * 3], suby[N * 3];
int tmp[N * 3];
bool wallr[N * 3][N * 3], wallc[N * 3][N * 3];

void preprocess() {
	int cnt, cnt_;
	cnt = 0;
	tmp[++cnt] = 0;
	for(int i = 1; i <= n; i++) tmp[++cnt] = r[i].x;
	for(int i = 1; i <= m; i++) tmp[++cnt] = c[i].stx, tmp[++cnt] = c[i].edx;
	std::sort(tmp + 1, tmp + cnt + 1);
	cnt_ = std::unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
	zerox = std::lower_bound(tmp + 1, tmp + cnt_ + 1, 0) - tmp;
	for(int i = 1; i <= n; i++) r[i].x = std::lower_bound(tmp + 1, tmp + cnt_ + 1, r[i].x) - tmp;
	for(int i = 1; i <= m; i++) {
		c[i].stx = std::lower_bound(tmp + 1, tmp + cnt_ + 1, c[i].stx) - tmp;
		c[i].edx = std::lower_bound(tmp + 1, tmp + cnt_ + 1, c[i].edx) - tmp;
	}
	// subx[1] = subx[cnt_ + 1] = INF;
	for(int i = 2; i <= cnt_; i++) subx[i] = tmp[i] - tmp[i - 1];
	h = cnt_;
	///
	cnt = 0;
	tmp[++cnt] = 0;
	for(int i = 1; i <= m; i++) tmp[++cnt] = c[i].y;
	for(int i = 1; i <= n; i++) tmp[++cnt] = r[i].sty, tmp[++cnt] = r[i].edy;
	std::sort(tmp + 1, tmp + cnt + 1);
	cnt_ = std::unique(tmp + 1, tmp + cnt + 1) - tmp - 1;
	zeroy = std::lower_bound(tmp + 1, tmp + cnt_ + 1, 0) - tmp;
	for(int i = 1; i <= m; i++) c[i].y = std::lower_bound(tmp + 1, tmp + cnt_ + 1, c[i].y) - tmp;
	for(int i = 1; i <= n; i++) {
		r[i].sty = std::lower_bound(tmp + 1, tmp + cnt_ + 1, r[i].sty) - tmp;
		r[i].edy = std::lower_bound(tmp + 1, tmp + cnt_ + 1, r[i].edy) - tmp;
	}
	// suby[1] = suby[cnt_ + 1] = INF;
	for(int i = 2; i <= cnt_; i++) suby[i] = tmp[i] - tmp[i - 1];
	w = cnt_;
}

const int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
bool vis[N * 3][N * 3];
LL bfs(int stx_, int sty_) {
	LL ans = 0;
	std::queue<std::pair<int, int>> q;
	q.push({stx_, sty_});
	vis[stx_][sty_] = true;
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		ans += subx[x] * suby[y];
		// printf("(%lld, %lld)\n", x, y);
		for(int i = 0; i < 4; i++) {
			int dx = x + dir[i][0], dy = y + dir[i][1];
			if(vis[dx][dy]) continue;
			// printf("    -> (%lld, %lld) ", dx, dy);
			if((i == 0 && wallr[dx][dy]) || (i == 1 && wallc[dx][dy]) || (i == 2 && wallr[x][y]) || (i == 3 && wallc[x][y]))
				{ /* puts("×"); */ continue; }
			if(dx == 1 || dx == h + 1 || dy == 1 || dy == w + 1) return -1;
			// printf("√\n");
			vis[dx][dy] = true;
			q.push({dx, dy});
		}
	}
	return ans;
}

signed main() {
	scanf("%lld%lld", &m, &n);
	for(int i = 1; i <= m; i++) scanf("%lld%lld%lld", &c[i].stx, &c[i].edx, &c[i].y);
	for(int i = 1; i <= n; i++) scanf("%lld%lld%lld", &r[i].x, &r[i].sty, &r[i].edy);
	preprocess();
	for(int i = 1; i <= n; i++)
		for(int j = r[i].sty + 1; j <= r[i].edy; j++)
			wallr[r[i].x][j] = true;
	for(int i = 1; i <= m; i++)
		for(int j = c[i].stx + 1; j <= c[i].edx; j++)
			wallc[j][c[i].y] = true;
	LL ans = bfs(zerox, zeroy);
	if(ans == -1) puts("INF");
	else printf("%lld\n", ans);
	return 0;
} /*
2 2
-100 100 -100
-100 100 100
-100 -100 100
100 -100 100
*/