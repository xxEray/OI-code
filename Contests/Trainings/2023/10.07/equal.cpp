#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int b[N], c[2][N];

struct SegmentTree {
	int t[N << 2];
	void modify(int qind, int qv, int x = 1, int l = 1, int r = n + 1) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = n + 1) {
		if(ql > qr) return -INF;
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} segt[2], seg[2];

int suf[N];
int f[N][2];

void validate(int *cc) {
	int mx[2] = {0, 0}, cnt[2] = {0, 0};
	for(int i = 1; i <= n; i++) mx[cc[i]] = std::max(mx[cc[i]], a[i]), cnt[cc[i]] += (mx[cc[i]] == a[i]);
	if(cnt[0] != cnt[1]) cc[1] = 2;
}

int main() {
#ifndef DEBUG
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int mx = 0;
	for(int i = 1; i <= n; i++) mx = std::max(mx, a[i]), b[i] = (mx == a[i] ? 2 : 1);
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
	for(int i = 1; i <= n + 1; i++) segt[1].modify(i, -INF);
	for(int i = n; i >= 1; i--) {
		f[i][0] = segt[b[i] & 1].query(a[i] + 1, n + 1) + b[i];
		f[i][1] = segt[~b[i] & 1].query(a[i] + 1, n + 1) + b[i];
		segt[0].modify(a[i], f[i][0]), segt[1].modify(a[i], f[i][1]);
		// printf("f[%d]: %d %d\n", i, f[i][0], f[i][1]);
	}
	for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + (b[i] == 2);
	int cx = 0, cy = 0, mxx = 0, mxy = 0;
	for(int i = 1; i <= n; i++) seg[0].modify(a[i], f[i][0]), seg[1].modify(a[i], f[i][1]);
	for(int i = 1; i <= n; i++) {
		seg[0].modify(a[i], 0), seg[1].modify(a[i], 0);
		int should = cx + (mxx < a[i]) - cy + suf[i + 1];
		// printf("i = %d, cx = %d, cy = %d, mxx = %d, mxy = %d, should = %d\n", i, cx, cy, mxx, mxy, should);
		if(should >= 0 && seg[should & 1].query(mxy + 1, n + 1) >= should) c[0][i] = 0, cx += (mxx < a[i]), mxx = std::max(mxx, a[i]);
		else c[0][i] = 1, cy += (mxy < a[i]), mxy = std::max(mxy, a[i]);
	}
	cx = 0, cy = 0, mxx = 0, mxy = 0;
	for(int i = 1; i <= n; i++) seg[0].modify(a[i], f[i][0]), seg[1].modify(a[i], f[i][1]);
	for(int i = 1; i <= n; i++) {
		seg[0].modify(a[i], 0), seg[1].modify(a[i], 0);
		int should = cx - cy - (mxy < a[i]) + suf[i + 1];
		// printf("i = %d, cx = %d, cy = %d, mxx = %d, mxy = %d, should = %d\n", i, cx, cy, mxx, mxy, should);
		if(should >= 0 && seg[should & 1].query(a[i] + 1, n + 1) >= should) c[1][i] = 0, cy += (mxy < a[i]), mxy = std::max(mxy, a[i]);
		else c[1][i] = 1, cx += (mxx < a[i]), mxx = std::max(mxx, a[i]);
	}
	// printf("c[0]: "); for(int i = 1; i <= n; i++) printf("%d ", c[0][i]); puts("");
	// printf("c[1]: "); for(int i = 1; i <= n; i++) printf("%d ", c[1][i]); puts("");
	validate(c[0]), validate(c[1]);
	int id = 0;
	for(int i = 1; i <= n; i++) if(c[0][i] != c[1][i]) { id = (c[0][i] < c[1][i] ? 0 : 1); break; }
	if(c[id][1] == 2) puts("-1");
	else {
		for(int i = 1; i <= n; i++) printf("%d", c[id][i]);
		puts("");
	}
	return 0;
} /*
20
10 11 2 3 4 5 12 13 14 15 16 17 18 19 20 1 6 7 8 9 
*/