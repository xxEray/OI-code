#include <cstdio>
#include <algorithm>
#include <assert.h>

const int N = 200 + 5;
const int INF = 0x3f3f3f3f;

int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char a[N][N];
int t[N], d[N];
int n, m, Q;
int stx, sty;

int furniture[N][N][4];

struct SegmentTree {
	int t[N << 2];
	// 线段树没写，但是它过了……
	void set(int qind, int qv, int x = 1, int l = 1, int r = n) {
		t[qind] = qv;
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql > qr) return -INF;
		int ret = -INF;
		for(int i = ql; i <= qr; i++) ret = std::max(ret, t[i]);
		return ret;
	}
} segr[N][2][2], segc[N][2][2];

int main() {
	scanf("%d%d%d%d%d", &n, &m, &stx, &sty, &Q);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for(int i = 1; i <= Q; i++) { int x, y; scanf("%d%d%d", &x, &y, &d[i]); t[i] = y - x + 1, d[i]--; }
	for(int j = 1; j <= m; j++) {
		int last = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == 'x') last = i;
			furniture[i][j][0] = last;
		}
		last = n + 1;
		for(int i = n; i >= 1; i--) {
			if(a[i][j] == 'x') last = i;
			furniture[i][j][1] = last;
		}
	}
	for(int i = 1; i <= n; i++) {
		int last = 0;
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 'x') last = j;
			furniture[i][j][2] = last;
		}
		last = m + 1;
		for(int j = m; j >= 1; j--) {
			if(a[i][j] == 'x') last = j;
			furniture[i][j][3] = last;
		}
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 0; k < 4; k++) printf("furniture[%d][%d][%d] = %d%c", i, j, k, furniture[i][j][k], " \n"[k == 3]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		segr[i][0][0].set(j, -INF - j), segr[i][0][1].set(j, -INF + j);
		segc[j][0][0].set(i, -INF - i), segc[j][0][1].set(i, -INF + i);
	}
	segr[stx][0][0].set(sty, -sty), segr[stx][0][1].set(sty, sty);
	segc[sty][0][0].set(stx, -stx), segc[sty][0][1].set(stx, stx);
	for(int k = 1; k <= Q; k++) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(d[k] == 0) {
					int i_ = std::min(furniture[i][j][1] - 1, i + t[k]);
					int ret = segc[j][(k & 1) ^ 1][1].query(i, i_) - i;
					segr[i][k & 1][0].set(j, ret - j), segr[i][k & 1][1].set(j, ret + j);
					segc[j][k & 1][0].set(i, ret - i), segc[j][k & 1][1].set(i, ret + i);
				} else if(d[k] == 1) {
					int i_ = std::max(furniture[i][j][0] + 1, i - t[k]);
					int ret = segc[j][(k & 1) ^ 1][0].query(i_, i) + i;
					segr[i][k & 1][0].set(j, ret - j), segr[i][k & 1][1].set(j, ret + j);
					segc[j][k & 1][0].set(i, ret - i), segc[j][k & 1][1].set(i, ret + i);
				} else if(d[k] == 2) {
					int j_ = std::min(furniture[i][j][3] - 1, j + t[k]);
					int ret = segr[i][(k & 1) ^ 1][1].query(j, j_) - j;
					segr[i][k & 1][0].set(j, ret - j), segr[i][k & 1][1].set(j, ret + j);
					segc[j][k & 1][0].set(i, ret - i), segc[j][k & 1][1].set(i, ret + i);
				} else if(d[k] == 3) {
					int j_ = std::max(furniture[i][j][2] + 1, j - t[k]);
					int ret = segr[i][(k & 1) ^ 1][0].query(j_, j) + j;
					segr[i][k & 1][0].set(j, ret - j), segr[i][k & 1][1].set(j, ret + j);
					segc[j][k & 1][0].set(i, ret - i), segc[j][k & 1][1].set(i, ret + i);
				} else assert(0);
		// puts("-------");
		// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%2d%c", segr[i][k & 1][0].query(j, j) + j, " \n"[j == m]);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			ans = std::max(ans, segr[i][Q & 1][0].query(j, j) + j);
	printf("%d\n", ans);
	return 0;
}