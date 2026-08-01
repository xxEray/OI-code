#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
struct Node { int x, y; } a[N];

int tmp[N];
int cx, cy;
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++cx] = a[i].x;
	std::sort(tmp + 1, tmp + cx + 1);
	cx = std::unique(tmp + 1, tmp + cx + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].x = std::lower_bound(tmp + 1, tmp + cx + 1, a[i].x) - tmp;
	for(int i = 1; i <= n; i++) tmp[++cy] = a[i].y;
	std::sort(tmp + 1, tmp + cy + 1);
	cy = std::unique(tmp + 1, tmp + cy + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].y = std::lower_bound(tmp + 1, tmp + cy + 1, a[i].y) - tmp;
}

struct SegValue { int mx, cnt, sc; };
SegValue calc(SegValue x, const SegValue y) {
	SegValue z;
	z.mx = std::max(x.mx, y.mx);
	z.cnt = (x.mx == z.mx) * x.cnt + (y.mx == z.mx) * y.cnt;
	z.sc = std::max(x.mx == z.mx ? x.sc : x.mx, y.mx == z.mx ? y.sc : y.mx);
	return z;
}
struct SegmentTree {
	SegValue t[N << 2];
	int lz[N << 2];
	void setlazy(int x, int v) { t[x].mx = std::min(t[x].mx, v), lz[x] = std::min(lz[x], v); }
	void lazydown(int x) { setlazy(x << 1, lz[x]), setlazy(x << 1 | 1, lz[x]), lz[x] = INF; }
	void build(int x = 1, int l = 1, int r = cx) {
		lz[x] = INF, t[x].mx = 0, t[x].cnt = r - l + 1, t[x].sc = -INF;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int qv, int x = 1, int l = 1, int r = cx) {
		if(l == r) { t[x].mx = qv, t[x].sc = -INF, t[x].cnt = 1, lz[x] = INF; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	void setmin(int ql, int qr, int qv, int x = 1, int l = 1, int r = cx) {
		if(t[x].mx < qv) return;
		if(ql <= l && r <= qr && t[x].sc < qv) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) setmin(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) setmin(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	SegValue query(int ql, int qr, int x = 1, int l = 1, int r = cx) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return calc(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	discrete();
	seg.build();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.y < y.y; });
	LL ans = 0;
	for(int i = 1; i <= n; i++)  {
		// printf("(%d, %d)\n", a[i].x, a[i].y);
		if(a[i].x > 1) {
			seg.setmin(1, a[i].x - 1, a[i].x);
			auto res = seg.query(1, a[i].x - 1);
			if(res.mx == a[i].x) ans += res.cnt;
			// printf("ans = %lld\n", ans);
		}
		seg.modify(a[i].x, INF);
	}
	printf("%lld\n", ans);
	return 0;
}