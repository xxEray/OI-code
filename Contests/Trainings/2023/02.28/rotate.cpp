#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>

typedef long double LD;

const int N = 500 + 5;
const LD eps = 1e-12;
const LD PI = acosl(-1);

int n, m;
int x[N], y[N];
int a[N][N], sz[N];
LD m_atan2[N][N];
int st;

LD dist(LD i, LD j) { return sqrtl(i * i + j * j); }
bool cmp(int i, int j) {
	LD di = m_atan2[i][st], dj = m_atan2[j][st];
	if(fabsl(di - dj) <= eps) return dist(x[i] - x[st], y[i] - y[st]) < dist(x[j] - x[st], y[j] - y[st]);
	else return di < dj;
}
void preprocess() {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) m_atan2[i][j] = atan2(y[i] - y[j], x[i] - x[j]);
	for(int i = 1; i <= n; i++) {
		sz[i] = 0;
		for(int j = 1; j <= n; j++) if(j != i) a[i][++sz[i]] = j;
		st = i;
		std::sort(a[i] + 1, a[i] + sz[i] + 1, cmp);
	}
}

LD sum[N];
int cnt[N];
LD angle[N];
int solve(int sx, int sy, int tx, int ty, LD len) {
	for(int i = 1; i <= n; i++) sum[i] = -1, cnt[i] = 0, angle[i] = 0;
	int ans = 1, dx = tx, dy = ty, now = 0;
	st = 0, x[st] = sx, y[st] = sy, sz[0] = n;
	for(int i = 0; i <= n; i++) m_atan2[i][0] = atan2(y[i] - y[0], x[i] - x[0]), m_atan2[0][i] = atan2(y[0] - y[i], x[0] - x[i]);
	for(int i = 1; i <= n; i++) a[0][i] = i;
	std::sort(a[0] + 1, a[0] + n + 1, cmp);
	while(len >= eps) {
		// printf("[ans=%d] now=%d, (%d, %d) (len=%.3lf)\n", ans, now, x[now], y[now], len);
		int nxt = 0;
		int l = 1, r = sz[now] + 1;
		LD val = atan2(dy - y[now], dx - x[now]);
		while(l < r) {
			int mid = (l + r) >> 1;
			if(m_atan2[a[now][mid]][now] <= val + eps) l = mid + 1;
			else r = mid;
		}
		if(l > 1) l--;
		if(val <= m_atan2[a[now][1]][now] - eps) l = sz[now];
		int c = 0;
		while(++c <= n && dist(x[a[now][l]] - x[now], y[a[now][l]] - y[now]) >= len + eps) l = (l > 1 ? l - 1 : sz[now]);
		if(dist(x[a[now][l]] - x[now], y[a[now][l]] - y[now]) <= len + eps) nxt = a[now][l];
		if(nxt == 0) break;
		len -= dist(x[nxt] - x[now], y[nxt] - y[now]), dx = 2 * x[nxt] - x[now], dy = 2 * y[nxt] - y[now], now = nxt;
		ans++;
		if(sum[now] >= -eps && fabs(angle[now] - val) <= eps) {
			LD cyclel = sum[now] - len;
			int cycle = ans - cnt[now];
			int times = (int)(len / cyclel + eps);
			len -= cyclel * times, ans += cycle * times;
			// if(times) printf("speed up %d times (cycle length = %.3lf, cycle contribution = %d)\n", times, cyclel, cycle);
		}
		sum[now] = len, cnt[now] = ans, angle[now] = val;
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
		preprocess();
		for(int i = 1; i <= m; i++) {
			int sx, sy, tx, ty, len;
			scanf("%d%d%d%d%d", &sx, &sy, &tx, &ty, &len);
			printf("%d\n", solve(sx, sy, tx, ty, len));
		}
	}
	return 0;
} /*
1
3 1
-40 -4
46 -25
2 11
6941 -3655 -686 3229 10275
*/