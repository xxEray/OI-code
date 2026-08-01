#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 6e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
struct Block { int x, s, t; } a[N];
int q[N];

int elemcnt;
int tmp[N * 3];
void preprocess() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = a[i].s, tmp[++c] = a[i].t;
	for(int i = 1; i <= m; i++) tmp[++c] = q[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].s = std::lower_bound(tmp + 1, tmp + c + 1, a[i].s) - tmp;
	for(int i = 1; i <= n; i++) a[i].t = std::lower_bound(tmp + 1, tmp + c + 1, a[i].t) - tmp;
	for(int i = 1; i <= m; i++) q[i] = std::lower_bound(tmp + 1, tmp + c + 1, q[i]) - tmp;
	elemcnt = c;
}

struct SegmentTree {
	int t[N << 2], lazy[N << 2];
	int calc(int x, int y) { return std::min(x, y); }
	void init() { memset(t, 0x3f, sizeof(t)), memset(lazy, 0x3f, sizeof(lazy)); }
	void set_lazy(int x, int v) { if(lazy[x] > v) lazy[x] = v, t[x] = calc(t[x], v); }
	void lazy_down(int x) {
		set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]);
		lazy[x] = INF;
	}
	void setmin(int ql, int qr, int qv, int x = 1, int l = 1, int r = elemcnt) {
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) setmin(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) setmin(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = calc(t[x << 1], t[x << 1 | 1]);
	}
	int query(int qind, int x = 1, int l = 1, int r = elemcnt) {
		if(l == r) return t[x];
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qind <= mid) return query(qind, x << 1, l, mid);
		else return query(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].s, &a[i].t, &a[i].x), a[i].s -= a[i].x, a[i].t -= a[i].x + 1;
	for(int i = 1; i <= m; i++) scanf("%d", &q[i]);
	// for(int i = 1; i <= n; i++) printf("[%d, %d]: priority = %d\n", a[i].s, a[i].t, a[i].x);
	// for(int i = 1; i <= m; i++) printf("%d ", q[i]);
	// puts("");
	preprocess();
	// for(int i = 1; i <= n; i++) printf("[%d, %d]: priority = %d\n", a[i].s, a[i].t, a[i].x);
	// for(int i = 1; i <= m; i++) printf("%d ", q[i]);
	// puts("");
	std::sort(a + 1, a + n + 1, [](Block x, Block y) { return x.x < y.x; });
	seg.init();
	for(int i = 1; i <= n; i++) seg.setmin(a[i].s, a[i].t, a[i].x);
	for(int i = 1; i <= m; i++) {
		int t = seg.query(q[i]);
		if(t < INF) { printf("%d\n", t); continue; }
		puts("-1");
	}
	return 0;
}