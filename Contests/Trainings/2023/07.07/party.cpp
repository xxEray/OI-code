#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Node { int l, r, id; } a[N];

int tmp[2 * N];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++m] = a[i].l, tmp[++m] = a[i].r;
	std::sort(tmp + 1, tmp + m + 1);
	m = std::unique(tmp + 1, tmp + m + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		a[i].l = std::lower_bound(tmp + 1, tmp + m + 1, a[i].l) - tmp;
		a[i].r = std::lower_bound(tmp + 1, tmp + m + 1, a[i].r) - tmp;
	}
}

struct SegmentTree {
	int t[N * 8], lazy[N * 8];
	void build(int x = 1, int l = 1, int r = m) {
		t[x] = lazy[x] = INF;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void setlazy(int x, int v) { t[x] = std::min(t[x], v), lazy[x] = std::min(lazy[x], v); }
	void lazydown(int x) { setlazy(x << 1, lazy[x]), setlazy(x << 1 | 1, lazy[x]); lazy[x] = INF; }
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = m) {
		if(ql <= l && r <= qr) { setlazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	int query(int ql, int qr, int x = 1, int l = 1, int r = m) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg;

int lv[N], rv[N], ans[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	discrete();
	// for(int i = 1; i <= n; i++) printf("[%d, %d]\n", a[i].l, a[i].r);
	seg.build();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.r < y.r; });
	for(int i = 1; i <= n; i++) lv[a[i].id] = (a[1].r < a[i].l ? seg.query(a[i].l, a[i].r) + 1 : 0), seg.modify(a[i].r, a[i].r, lv[a[i].id]);
	seg.build();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.l < y.l; });
	for(int i = n; i >= 1; i--) rv[a[i].id] = (a[n].l > a[i].r ? seg.query(a[i].l, a[i].r) + 1 : 0), seg.modify(a[i].l, a[i].l, rv[a[i].id]);
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.id < y.id; });
	// for(int i = 1; i <= n; i++) printf("%d: lv = %d, rv = %d\n", i, lv[i], rv[i]);
	for(int i = 1; i <= n; i++) ans[i] = std::min(lv[i] + rv[i], INF);
	seg.build();
	for(int i = 1; i <= n; i++) seg.modify(a[i].l, a[i].r, lv[i] + rv[i] + 1);
	for(int i = 1; i <= n; i++) ans[i] = std::min(ans[i], seg.query(a[i].l, a[i].r));
	for(int i = 1; i <= n; i++) if(ans[i] >= INF) { puts("-1"); return 0; }
	long long out = 0;
	for(int i = 1; i <= n; i++) out += ans[i];
	printf("%lld\n", out);
	return 0;
} /*
4
83 106
101 111
33 92
98 100
*/